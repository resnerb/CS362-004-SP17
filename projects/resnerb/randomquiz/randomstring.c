/*Bryan Resner
 *CS362 - Quiz 2
 *April 30th, 2017*/

When initially looking through the code I recognized that to reach the error message the state variable had to reach a value of 9. The testme() function increments through states based on the specific Ascii character returned from the inputChar() function. Therefore we want the inputChar function to generate random characters over the entire Ascii character set. Once we are at state=9 testme() looks for the string 'reset' in order to produce the error message. Therefore I needed inputString() to return a string of five  random lowercase letters from the Ascii character set.


char inputChar()
{
    int r = rand() % 128;
    char c = r;
    return c;
}

OUTLINE: For inputChar I am randomly picking an ascii character based on the 128 ascii character set. Then I am  then casting the integer that is picking the ascii character to a char variable, which I return.

char *inputString()
{
    int r;
    int i;
    char c;
    char s[6];
    /*char avail_letters[4] = {'s', 't', 'r', 'e'};*/
    for(i = 0; i < 5; i++) {
        r = (rand() % 26) + 97;
        c = r;
        s[i] = c;
        /*r = rand() % 4;*/
        /*s[i] = avail_letters[r];*/
    }
    s[5] = '\0';
    
    return s;
}

OUTLINE: For inputString I am randomly picking an ascii character that is within the lower case letters range(Ascii Characters: 97-122). I tried a couple of approaches: 1) I allowed the string to be any five lowercase letters and randomly filled the string. Doing this caused many iterations to be run before it was able to print the error message. 2) I randomly picked among just the lowercase letters that make up the stopping word 'reset' when in state 9.

For the first approach I ran 5 iterations:
Trial 1: 759540 iterations before printing error
Trial 2: 13487005 iterations before printing error
Trial 3: 11601786 iterations before printing error
Trial 4: 1076144 iterations before printing error
Trial 5: 11859525 iterations before printing error

For the second approach I ran 5 iterations:
Trial 1: 1860 iterations before printing error
Trial 2: 3725 iterations before printing error
Trial 3: 984 iterations before printing error
Trial 4: 3327 iterations before printing error
Trial 5: 903 iterations before printing error

Based on these results a more thorough random testing approach is when we select any lowercase character as oppposed to just the characters in the stopping word. If we were to allow any of the 128 Ascii characters it would generate even more iterations.