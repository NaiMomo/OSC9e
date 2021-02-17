This contains source code for the 9th edition of
"Operating System Concepts" by Silberschatz/Galvin/Gagne.
Published by John Wiley & Sons.

Additions made by Liam Paull at University of Montreal for the class IFT2245.
Some fixes by Samuel Yvon at University of Montreal for the class IFT2245.


Source files are organized by Chapter. (Each chapter has a
separate README file.)


# Getting Started

## On native Linux

simply clone the repository and compile and follow the instructions in the individual chapters:

    git clone https://github.com/liampaull/OSC9e.git


## On MacOSX or Windows

A good and reliable option is to run things in a Docker environment.

1. Download and [install docker](https://www.docker.com/get-started) (click appropriate button on the right hand side)

2. Clone this repo:

    `git clone https://github.com/liampaull/OSC9e.git`

3. Make sure the docker daemon is running (by default it should start on startup but, for example on MacOSx you should see the whale with containers on it icon in your system tray at the top) 

4. Run a docker container and mount the directory you just cloned:

   ``docker run -it -v `pwd`/OSC9e:/OSC9e gcc``

where `` `pwd`/OSC9e`` is the full path to the `OSC9e` directory. `gcc` is just a ubuntu docker image with the `gcc` compiler already installed. 

You are now entered into a clean ubuntu environment and you should see the folder `OSC9e` if you do `ls`. You can enter the folder with

    cd OSC9e

and now enter the desired folder that you want follow the specific instructions.

5. If you want to edit files to try things out (recommended)

   ```
   apt update
   apt install emacs
   ```
or whatever editor you like (but emacs is the best :) )


