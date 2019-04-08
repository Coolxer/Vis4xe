# Vis4xe
The application to organize your's Arduino screens in big project. It enables to plan your subtitles on screen

![3](https://user-images.githubusercontent.com/22798873/55751974-39c68480-5a47-11e9-9362-46a4a73b8ff0.png)

## Install
Just download/clone repository and inside app folder you can find Vis4xe.exe file, using to run application.

## About
The application is written with C++ language using Qt library. It has file managment I/O system( json files service and txt
for generate arduino code ready to use with Liquid Crystal library https://www.arduino.cc/en/Reference/LiquidCrystal) 
and ability to remember last opened projects for fast continue work.

## How to use

### Add project
The interface is user-friendly. If you dont have any projects created you just click the "New" button,
then you have to choose your project name, number of rows(1 - 10), cols(1 - 24) and confirm with "+" (plus) button

![1](https://user-images.githubusercontent.com/22798873/55751742-b4db6b00-5a46-11e9-9f52-000923f8205b.png)

### Edit Project
After created project/ opened from file you will see the edit screen. Here you can add the string to the list (on right side)
and then grab it on the screen. The string list has limit to 10 strings in one time, but you can drag it on lcd or delete to add new.
If you clicked on the string it will change the color to red. That means you activited the edit mode in which you can move
the strings on the lcd cells using arrow keys. If you want to exit edit mode without saving, press Escape (ESC) button, else if 
you want to accept your changes press Enter button. 

![2](https://user-images.githubusercontent.com/22798873/55751877-f9ff9d00-5a46-11e9-867b-10cc425ad5d2.png)


Notice the buttons Colors (Save and Add Btn), because their colors are changing according to the situation( changes made / can string be added?)

## Info
The program will create the folder with the projects list (using for fast opening project, without looking up through all folders)
inside C:\Users\User\Documents named Vis4xe that consists projects.json file. Do not remove it

## Author
Łukasz "Coolxer" Miłoś

## License
This project is licensed under the MIT License - see the LICENSE.md file for details
