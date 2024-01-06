#include "Day.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    // create a window
    RenderWindow window( VideoMode(1280, 720), "Weekly Calendar" );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // load in the font file so that it can be used when creating text objects
    Font font;
    if (!font.loadFromFile("RobotoFontFile/RobotoCondensed-Regular.ttf")) {
        cerr << "Error loading font." <<endl;
        return EXIT_FAILURE;
    }
    //  END  ANY FILE LOADING
    /////////////////////////////////////

    Event event;

    // create background calendar image:
    vector<RectangleShape> vCalendar;

    float colWidth = 168.57142f;
    float colHeight = 720.0f - 10.0f - 10.0f; 

    // create 7 columns which will represent days
    for (int i = 0; i < 7; i++) {
        RectangleShape dayColumn(Vector2f(colWidth, colHeight)); 
        dayColumn.setFillColor(Color(255, 255, 255, 128));
        dayColumn.setOutlineColor(Color::Black);
        dayColumn.setOutlineThickness(2.0f);
        dayColumn.setPosition(80.0f + colWidth * i, 10.0f);
        vCalendar.push_back(dayColumn);
    }

    float rowWidth = 1280.0f - 10.0f - 10.0f; 
    float rowHeight = 50.769f;

    // create 12 rows which will represent 12 hours (8 am to 8 pm)
    for (int i = 0; i < 12; i++) {
        RectangleShape dayRow(Vector2f(rowWidth, rowHeight));
        dayRow.setFillColor(Color(255, 255, 255, 128));
        dayRow.setOutlineColor(Color::Black);
        dayRow.setOutlineThickness(2.0f);
        dayRow.setPosition(0, 40.0f + rowHeight * i);
        vCalendar.push_back(dayRow);
    }

    // create a vector of text objects which will display the hour 
    vector<Text> vHours;

    for (int i = 0; i < 13; i++) {
        int intHour = 8 + i; 
        string meridiem = "AM"; 
        Text hour; 
        hour.setFont(font);

        if (intHour > 12) { // if it is 12 noon or later, then display PM instead of AM
            meridiem = "PM";
            intHour -= 12; 
        }

        string hourOut = to_string(intHour) + meridiem; 
        hour.setString(hourOut); 

        hour.setCharacterSize(25);
        hour.setFillColor(Color::Black);
        hour.setPosition(15.0f, 40.0f + rowHeight * i);

        intHour++; 
        vHours.push_back(hour);
    }

    // create a vector of borders (these are purely to make the window look more aesthetically pleasing)
    vector<RectangleShape> vBorders; 

    RectangleShape leftBorder(Vector2f(10.0f, 720.0f));
    leftBorder.setFillColor(Color::White);
    leftBorder.setOutlineColor(Color::Black);
    leftBorder.setOutlineThickness(2.0f);
    leftBorder.setPosition(0, 0);
    vBorders.push_back(leftBorder);

    RectangleShape topBorder(Vector2f(1280.0f, 40.0f));
    topBorder.setFillColor(Color::White);
    topBorder.setOutlineColor(Color::Black);
    topBorder.setOutlineThickness(2.0f);
    topBorder.setPosition(0,0);
    vBorders.push_back(topBorder);

    RectangleShape bottomBorder(Vector2f(1280.0f, 40.0f));
    bottomBorder.setFillColor(Color::White);
    bottomBorder.setOutlineColor(Color::Black);
    bottomBorder.setOutlineThickness(2.0f);
    bottomBorder.setPosition(0, 720.0f - 18.0f);
    vBorders.push_back(bottomBorder);

    // create a vector of day objects. I called these objects buttons because you will be able to press them in order to create a task
    vector<Day> vDayButtons; 

    for (int i = 0; i < 7; i++) {
        Day newDay = Day(i);
        vDayButtons.push_back(newDay); 
    }


    // while the window is open
    while( window.isOpen() ) {

        // clear any existing contents and set the background color
        window.clear(Color::White); 

        /////////////////////////////////////
        // BEGIN DRAWING HERE - DRAW EVERYTHING IN ORDER!!

        // draw each object for each vector
        for (unsigned int i = 0; i < vCalendar.size(); i++) { 
            window.draw(vCalendar[i]);
        }

        for (unsigned int i = 0; i < vHours.size(); i++) {
            window.draw(vHours[i]);
        }

        for (unsigned int i = 0; i < vBorders.size(); i++) {
            window.draw(vBorders[i]);
        }

        for (unsigned int i = 0; i < vDayButtons.size(); i++) {
            vDayButtons[i].draw(window, i, font);
        }

        for (unsigned int i = 0; i < vDayButtons.size(); i++) {
            for (unsigned int i = 0; i < vDayButtons.size(); i++) {
                // draw each task within each day
                vDayButtons[i].drawAllTasks(window, font);
            }
        }

        //  END  DRAWING HERE
        /////////////////////////////////////


        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                // if the red x in the top corner is pressed, close the window
                window.close();
            } else if (event.type == Event::KeyPressed) {
                // if escape key is pressed close the window and delete each task in the day object
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                    for (unsigned int i = 0; i < vDayButtons.size(); i++) {
                        vDayButtons[i].deleteAllTasks(); 
                    }
                }
            } else if (event.type == Event::MouseButtonPressed) {
                // if the left mouse button is pressed, check to see if the cursor is within the bounds of the day button
                // if it is within bounds, create a task for that day
                if (event.mouseButton.button == Mouse::Left) {
                    // check if the mouse is within bounds of any of the day buttons
                    for (unsigned int i = 0; i < vDayButtons.size(); i++) {
                        if (vDayButtons[i].isMouseOver(window)) {
                            // cout << vDayButtons[i].getNameStr() << " worked!" <<endl; 
                            vDayButtons[i].createTask();
                        }
                    }
                }
                
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
    }
    return 0;
}
