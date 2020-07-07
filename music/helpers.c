// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{

    //Number of 8ths = (numerator x 8) / denominator
    return ((fraction[0] - 0x30) * 8) / (fraction[2] - 0x30);

}



// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Initializations
    char pitch = note[0];
    double distance = 0;
    int octave;
    int base;

    //Check whether note contains accidentals
    if (strlen(note) > 2)
    {
        char accidental = note[1];
        octave = note[2] - 0x30;

        //Shift up/down accordingly
        if (accidental == '#')
        {
            distance++;
        }
        else if (accidental == 'b')
        {
            distance--;
        }
    }
    else
    {
        octave = note[1] - 0x30;
    }

    //Calculate note distance from A4 (after accidentals)
    switch (pitch)
    {
        case 'B':
            distance = (distance + 2);
            break;
        case 'G':
            distance = (distance - 2);
            break;
        case 'F':
            distance = (distance - 4);
            break;
        case 'E':
            distance = (distance - 5);
            break;
        case 'D':
            distance = (distance - 7);
            break;
        case 'C':
            distance = (distance - 9);
            break;
    }

    double oct = (double)octave;

    //If not in 4th octave multiply/divide accordingly. Otherwise don't.
    if (octave != 4)
    {
        base = round((pow(2, (distance / 12)) * 440) * (pow(2, (oct - 4))));
    }
    else
    {
        base = round(pow(2, (distance / 12)) * 440);
    }

    return base;

}


// Determines whether a string represents a rest
bool is_rest(string s)
{
    //If string contains anything, it's not a rest
    if (strlen(s) > 0)
    {
        return false;
    }

    return true;
}