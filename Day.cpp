#include "Day.h"

using namespace sf; 
using namespace std; 

// create a day object and set its position based on which day of the week it is 
Day::Day(const int DAY_VALUE) {

    _dayValue = DAY_VALUE; 
    float colWidth = 168.57142f;
    float colX = 80.0f + colWidth * (_dayValue);
    _dayShape.setSize(Vector2f(colWidth, 40.0f));
    _dayShape.setFillColor(Color::White);
    _dayShape.setOutlineColor(Color::Black);
    _dayShape.setOutlineThickness(2.0f);
    _dayShape.setPosition(colX, 0);
}

Day::~Day() {
    // deleteAllTasks();
}

// create a task using input from the user
void Day::createTask () {
    Task newTask;
    cout <<endl <<"NEW TASK: " <<endl; 

    cout << "Enter task name: ";
    cin >> newTask.tName; 


    // ensure that the start time is valid
    do {
        cout << "Enter task start time (8-20 = 8AM-8PM): "; 
        cin >> newTask.tStartTime;
        if (newTask.tStartTime < 8 || newTask.tStartTime > 20) {
            cout << "Invalid start time." << endl;
        }
    } while (newTask.tStartTime < 8 || newTask.tStartTime > 20); 

    // end time is one hour after the start time
    newTask.tEndTime = newTask.tStartTime + 1; 

    // ensure that the color is valid 
    string tColor;
    do {
        cout << "Enter a color for the task ('R', 'O', 'Y', 'G', 'B', 'I', 'V'): "; 
        cin >> tColor; 
        if (!(tColor == "R"||tColor == "O"||tColor == "Y"||tColor == "G"||tColor == "B"||tColor == "I"||tColor == "V")) {
            cout << "Invalid color." << endl;
        }
    } while (!(tColor == "R"||tColor == "O"||tColor == "Y"||tColor == "G"||tColor == "B"||tColor == "I"||tColor == "V"));


    float colWidth = 168.57142f;
    float rowHeight = 50.769f; 
    newTask.tShape.setSize(Vector2f(colWidth, rowHeight));

    // if the color value is a certain letter, draw that task shape with its respective color 
    if (tColor == "R") {
        newTask.tShape.setFillColor(Color::Red);
    } else if (tColor == "O") {
        newTask.tShape.setFillColor(Color(255,165,0));
    } else if (tColor == "Y") {
        newTask.tShape.setFillColor(Color::Yellow);
    } else if (tColor == "G") {
        newTask.tShape.setFillColor(Color::Green);
    } else if (tColor == "B") {
        newTask.tShape.setFillColor(Color::Blue);
    } else if (tColor == "I") {
        newTask.tShape.setFillColor(Color(75,0,130));
    } else if (tColor == "V") {
        newTask.tShape.setFillColor(Color(238,130,238));
    } else {
        cerr << "Error getting tColor value" <<endl; 
    }

    newTask.tShape.setOutlineColor(Color::Black);
    newTask.tShape.setOutlineThickness(2.0f);

    // set the position of the task based on its start time
    float xPos = 80.0f + colWidth * (_dayValue); 
    float yPos = 40.0f + rowHeight * (newTask.tStartTime - 8); // start times are between 8-20 so they need to be offset by 8
    newTask.tShape.setPosition(xPos, yPos); // xPos based on day of the week, yPos based on start time

    _vDayTasks.push_back(newTask);
}

// delete all tasks for the day
void Day::deleteAllTasks() {
    _vDayTasks.erase(_vDayTasks.begin());
}

// get the name of the day
Text Day::getName () {
    return this->_dayName; 
}

// for testing 
string Day::getNameStr() {
    string strName = (this->_dayName).getString().toAnsiString();
    return strName;
}

// draw the day object based on the values that have already been set
void Day::draw (RenderWindow& window, const int DAY_VALUE, const Font FONT) {

    _dayValue = DAY_VALUE; 
    float colWidth = 168.57142f;
    string dayString; 
    // text objects only worked when their creation was in the same function as drawing them
    switch (_dayValue) {
    case 0:
        dayString = "Sunday";
        break;
    case 1:
        dayString = "Monday";
        break;
    case 2:
        dayString = "Tuesday";
        break;
    case 3:
        dayString = "Wednesday";
        break;
    case 4:
        dayString = "Thursday";
        break;
    case 5:
        dayString = "Friday";
        break;
    case 6:
        dayString = "Saturday";
        break;
    default:
        dayString = "ERROR";
        break;
    }

    _dayName.setString(dayString); 
    _dayName.setFont(FONT);
    _dayName.setCharacterSize(25);
    _dayName.setFillColor(Color::Black);

    float colX = 80.0f + colWidth * (_dayValue);
    FloatRect textBounds = _dayName.getLocalBounds();
    float textX = colX + (colWidth - textBounds.width) / 2.0f;
    float textY = (40.0f - textBounds.height) / 2.0f;
    _dayName.setPosition(textX, textY); 

    window.draw(this->_dayShape);
    window.draw(_dayName);
}

void Day::drawAllTasks (RenderWindow& window, const sf::Font FONT) {
    
    // for each task in the vector of tasks, draw the task 
    for (unsigned int i = 0; i < _vDayTasks.size(); i++) {
        Task taskToDraw = _vDayTasks[i]; 
        
        float colWidth = 168.57142f;
        float rowHeight = 50.769f; 

        // again it was necessary that i set the Text values in the same function that it was being drawn in 
        Text tNameText; 
        tNameText.setString(taskToDraw.tName);
        tNameText.setFont(FONT);
        tNameText.setCharacterSize(25);
        tNameText.setFillColor(Color::Black);

        // get the position of the task shape, so that the text can be drawn within that shape
        float colX = 80.0f + colWidth * (_dayValue);
        FloatRect textBounds = taskToDraw.tShape.getLocalBounds();
        float textX = colX + (colWidth - textBounds.width) / 2.0f;
        float textY = 40.0f + rowHeight * (taskToDraw.tStartTime - 8);
        tNameText.setPosition(textX, textY);

        window.draw(taskToDraw.tShape); 
        window.draw(tNameText);
    }
}

bool Day::isMouseOver (RenderWindow& window) {
    // map the mouse position to the window, then get the bounds of the day shape and see if the mouse pos is within the day shape pos
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f mappedMousePos = window.mapPixelToCoords(mousePos);
    return _dayShape.getGlobalBounds().contains(mappedMousePos);
}