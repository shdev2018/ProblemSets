import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Get username
def getuser():
    user = db.execute("SELECT username FROM users WHERE id = :idnum",
                      idnum=session["user_id"])
    return user[0]['username']


# Gets password
def getbalance():
    balance = db.execute("SELECT cash FROM users WHERE id = :idnum",
                         idnum=session["user_id"])
    balance = float(balance[0]['cash'])
    return balance


# Gets total stocks bought & sold
def getquantities(symbol):
    user = getuser()
    bought = db.execute("SELECT SUM(quantity) FROM :user WHERE transaction_type = 'Purchase' AND stock_ticker = :ticker",
                        user=user, ticker=symbol)
    sold = db.execute("SELECT SUM(quantity) FROM :user WHERE transaction_type = 'Sale' AND stock_ticker = :ticker",
                      user=user, ticker=symbol)
    return bought[0]['SUM(quantity)'], sold[0]['SUM(quantity)']


# Returns list of comapnies invested in by user
def getcompanies(user):
    return [d['stock_ticker'] for d in db.execute("SELECT DISTINCT stock_ticker FROM :user", user=user)]


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # User logged in
    user = getuser()

    # Current Cash Balance
    balance = getbalance()

    # Check whether user owns any assets
    count = db.execute("SELECT COUNT (*) FROM :user", user=user)

    if len(count) > 0:

        companies = getcompanies(user)

        # Generate home table data
        compinfo = {}
        for company in companies:
            numbought, numsold = getquantities(company)
            if not numsold:
                numsold = 0
            if numbought - numsold > 0:
                currentinfo = lookup(company)
                compinfo[company] = [currentinfo.get('name'), float(currentinfo.get('price')), numbought - numsold]

        holding = 0.00

        # calculate totals
        for value in compinfo.values():
            value.append(float(value[1] * value[2]))
            holding += value[3]

        netvalue = holding + balance

        return render_template("index.html", user=user, balance=balance, stockinfo=compinfo, holding=holding, netvalue=netvalue)

    else:
        return render_template("index.html", user=user, balance=balance, holding=0, netvalue=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html", ticker=None)

    # check whether accessed via index link
    else:
        if not request.form.get("ticker"):

            # lookup quotes
            stock = lookup(request.form.get("symbol"))

            if not stock:
                return apology("Stock Doesn't Exist", 400)

            shares = 0

            # Check shares is a positive integer
            if request.form.get("shares").isdigit():
                shares += int(request.form.get("shares"))

            if shares < 1:
                return apology("Incorrect Input", 400)

            # Check users balance
            balance = getbalance()

            # Attempt to subtract stock price * shares
            if balance - (float(stock.get('price')) * shares) < 0:
                return apology("Cannot complete. Insufficient funds", 400)
            else:
                cost = float(stock.get('price')) * shares

            # If successful, add transaction to users db
            db.execute("INSERT INTO :user (transaction_type, stock_ticker, quantity, transfer) VALUES ('Purchase', :ticker, :quantity, :cost)",
                       user=getuser(), ticker=stock.get('symbol'), quantity=shares, cost=cost)

            # Update balance
            db.execute("UPDATE users SET cash=:newbalance WHERE id = :idnum",
                       newbalance=balance - cost, idnum=session["user_id"])

            return redirect("/")

        # Auto-populate ticker field
        else:
            return render_template("buy.html", ticker=request.form.get("ticker"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user = getuser()

    # Get transaction History
    history = db.execute("SELECT * FROM :user ORDER BY transaction_id DESC",
                         user=user)

    # Configure History for table
    tablefields = []
    i = 0
    for d in history:
        tablefields.append([])
        for value in d.values():
            tablefields[i].append(value)
        i += 1

    return render_template("history.html", user=user, history=tablefields)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        confirmation = request.form.get("confirmation")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Check if username already exists
        if len(rows) > 0:
            return apology("username unavailable", 400)

        # Compare password & confirmation
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Store data in database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :passhash)",
                   username=request.form.get("username"), passhash=generate_password_hash(request.form.get("password")))

        # Create personal data table
        db.execute("CREATE TABLE :username ('transaction_id' integer PRIMARY KEY AUTOINCREMENT NOT NULL, 'transaction_type' text NOT NULL, 'stock_ticker' text NOT NULL, 'quantity' integer NOT NULL, 'transfer' numeric(2) NOT NULL, 'time' datetime NOT NULL DEFAULT CURRENT_TIMESTAMP)",
                   username=request.form.get("username"))

        # Redirect user to home page
        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If reached via GET
    if request.method == "GET":
        return render_template("quote.html")

    else:
        # lookup quotes
        quotes = lookup(request.form.get("symbol"))

        # Check for valid symbol
        if not quotes:
            return apology("incorrect input", 400)

        # pass to template
        return render_template("quoted.html", quotes=quotes)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":

        # Get list of current assets
        companies = getcompanies(getuser())
        complist = []
        for company in companies:
            numbought, numsold = getquantities(company)
            if not numsold:
                numsold = 0
            if numbought - numsold > 0:
                complist.append(company)

        return render_template("sell.html", companies=complist)

    else:
        # lookup quotes
        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("Stock Doesn't Exist", 400)

        shares = 0

        # Check shares is a positive integer
        if request.form.get("shares").isdigit():
            shares += int(request.form.get("shares"))

        if shares < 1:
            return apology("Incorrect Input", 400)

        # check user owns suffient stocktype
        numbought, numsold = getquantities(stock.get('symbol'))

        if not numbought:
            return apology("You don't own this stock", 400)
        else:
            if not numsold:
                numsold = 0

        if (numbought - numsold) - shares < 0:
            return apology("Insuffient stock", 400)
        else:
            quantity = (numbought - numsold) - shares

        # calculate yeild
        yeild = float(stock.get('price')) * shares

        # If successful, add transaction to users db
        db.execute("INSERT INTO :user (transaction_type, stock_ticker, quantity, transfer) VALUES ('Sale', :ticker, :quantity, :yeild)",
                   user=getuser(), ticker=stock.get('symbol'), quantity=shares, yeild=yeild)

        # Update balance
        db.execute("UPDATE users SET cash=:newbalance WHERE id = :idnum",
                   newbalance=getbalance() + yeild, idnum=session["user_id"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)