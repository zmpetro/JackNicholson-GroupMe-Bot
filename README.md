JackNicholson-GroupMe-Bot
=========================

This application sends a random Jack Nicholson quote or meme into a GroupMe group through a GroupMe bot specified by the user.

How it works
------------

1. There are 29 quotes and 27 image URLs in the file `quotes.txt`, adding up to 56 possible messages. Quotes and images can be added as long as the random number generator upper bound is incremented. Note that the URL must be for an image hosted by GroupMe's image service. To get your images on their image service, you need to first upload them to their image service. See the documentation on how: [Image Service Documentation](https://dev.groupme.com/docs/image_service)

2. The random number generator generates a number between 1 and 56. The generator checks to make sure this number is not already contained in the file `previous.dat`. If the number is already contained in `previous.dat`, the random number generator continues to generate a random number until a number not contained in `previous.dat` is successfully generated. It then adds the number to `previous.dat`. If all numbers between 1 and 56 are contained in `previous.dat`, the program erases all numbers within `previous.dat`. This process ensures that a new message is generated every time the program is run.

3. The program stores either the quote or the URL contained in `quotes.txt` corresponding to the number generated by the random number generator.

4. The program formats an `HTTP POST` body and writes it to `message.dat`. The program then sends the `HTTP POST` to the GroupMe servers using `cURL`. This posts the message to the respective group chat.

Installation
------------

1. Create a GroupMe bot and add it to a group following the [GroupMe documentation](https://dev.groupme.com/tutorials/bots). `Callback URL` does not need to be specified.

2. Download `jack.c` and the 3 data files and add your bot ID found on the GroupMe website into `jack.c` where it says `insert bot ID here`.

3. Make sure [cURL](https://curl.haxx.se/download.html) is installed.

4. Compile `jack.c`.


Usage
-----

* Run the compiled executable file.

Example
-------

![alt screen1](https://raw.githubusercontent.com/zmpetro/JackNicholson-GroupMe-Bot/master/examples/screen1.png)
![alt screen2](https://raw.githubusercontent.com/zmpetro/JackNicholson-GroupMe-Bot/master/examples/screen2.png)

