READ ME: Active City by Soud Al Kharji, Yousif Alhajji, Eirini Theodorakopoulou, Viraj Jaswani

Download files: download and extract the zip folder ec327projfiles.zip, which contains all the necessary files to run the software.

To open the software:
In the terminal, navigate to the directory where you have stored the files then enter the following three lines:
g++ active_city.cpp -c
g++ active_city.o -o active_city -lsfml-graphics -lsfml-window -lsfml-system -lcurl
./active_city

Once in the application, use your cursor to select whatever city you would like to visit which should take you to the time/weather page and upon clicking the textbox (which should turn green indicating that it has been selected)
you will be able to type up to four characters. After the entry of the desired time, click "Go!" in the bottom right to see the suggested activities.

At any point outside of the homepage, press the back button to go to the previous page.
