import nltk


# Split string into lines and store in list
def splitlines(strng):
    line_list = [[]]
    i = 0
    for char in strng:
        if char == '\n':
            line_list[i] = ''.join(line_list[i])
            i += 1
            line_list.append([])
        else:
            line_list[i].append(char)
    line_list[i] = ''.join(line_list[i])
    return line_list


def lines(a, b):
    """Return lines in both a and b"""
    identical_lines = []

    # Tokenize lines
    lines_a = splitlines(a)
    lines_b = splitlines(b)

    # Store identical lines in list
    for line in lines_a:
        if lines_b.count(line) > 0:
            identical_lines.append(line)

    return identical_lines


def sentences(a, b):
    """Return sentences in both a and b"""
    identical_sentences = []

    # Tokenize sentences
    sentences_a = list(set(nltk.tokenize.sent_tokenize(a, language='english')))

    # Store identical sentences in list
    for sentence in sentences_a:
        if b.count(sentence) > 0:
            identical_sentences.append(sentence)

    return identical_sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    identical_subs = []
    sublist = []
    temp = ''

    # Fill buffer
    for i in range(len(a) - (n - 1)):
        temp = a[i:(i + n)]
        sublist.append(temp)

    # Remove duplicates
    sublist = list(set(sublist))

    # Add to list
    for sub in sublist:
        if b.count(sub) > 0:
            identical_subs.append(sub)

    return identical_subs