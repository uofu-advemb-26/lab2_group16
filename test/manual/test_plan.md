Lab 2 Manual Test Plan:

1. Make sure you are able to successfully flash your Pico and communicate to it through the terminal.

2. Flash the program. The LED should start intermittently blinking. If it doesn't then the blink_task wasn't reached.

3. Debug messages should show up on the terminal. One for each function reached for a total of 3 messages.

4. Try typing characters into the terminal. If the character is a letter, a letter of the opposite case should be printed. Otherwise, the character itself is printed instead.

    - KNOWN BUG: Pressing the enter key doesn't start a new line as it should. It just moves the cursor back to the start of the line.
    - KNOWN BUG: Pressing the delete key moves the cursor back one character, but doesn't delete.