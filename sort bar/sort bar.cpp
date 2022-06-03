#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <TGUI/TGUI.hpp>
#include <vector>
#include <array>
#include <cstdlib>


const sf::Vector2f windowSize = sf::Vector2f(1600.f, 800.f);

class Logic;
class Sort {
private:

	int partition(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int start, int end);
	// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
	void merge(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int const left, int const mid, int const right);
	
	void swap(std::vector <sf::RectangleShape>& bars, int i, int k);

public:
	void randomize(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui);

	void Bubble(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui);

	void insertionSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui);

	// begin is for left index and end is
	// right index of the sub-array
	// of arr to be sorted */
	void mergeSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int const begin, int const end);

	void quickSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int start, int end);
};

class Logic {
	bool toggled = true;
	bool buttonPressed = false;
	sf::Vector2f panelPos;
public:
	Sort sort;
	
	std::vector <sf::RectangleShape>bars;
	
	tgui::GuiSFML gui;
	
	Logic(sf::RenderWindow& window) {
		setup(window);
	}
	Logic() {
	
	}
	//sets up the gui
	void setup(sf::RenderWindow &window) {

		sf::Color textColour = sf::Color(166, 167, 163);

		tgui::Theme theme("C:/TGUI-0.9/themes/Black.txt");

		gui.setTarget(window);
		auto panel = tgui::Panel::create({ "25%", "100%" });;
		gui.add(panel);
		panel->setPosition(windowSize.x - panel->getFullSize().x, 0);
		panel->setRenderer(theme.getRenderer("Panel"));

		auto label = tgui::Label::create("Type of sorting:");
		label->getRenderer()->setTextColor(textColour);
		label->setOrigin(0.5, 0.5);
		label->setPosition({ "50%","10%" });
		label->setTextSize(25);
		panel->add(label,"Panel");
		panelPos = panel->getPosition();
		auto comboBox = tgui::ComboBox::create();
		comboBox->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		comboBox->getRenderer()->setArrowBackgroundColor(sf::Color(21, 21, 21));
		comboBox->getRenderer()->setArrowBackgroundColorHover(sf::Color(41, 41, 41));
		comboBox->getRenderer()->setBackgroundColorDisabled(sf::Color(61, 62, 63));
		comboBox->getRenderer()->setTextColor(textColour);
		comboBox->setSize({ "70%","5%" });
		comboBox->setOrigin(0.5, 0.5);
		comboBox->setPosition({ "50%","20%" });
		comboBox->setTextSize(25);
		comboBox->addItem("Bubble Sort");
		comboBox->addItem("Insertion Sort");
		comboBox->addItem("Merge Sort");
		comboBox->addItem("Quick Sort");
		comboBox->setSelectedItem("Bubble Sort");
		panel->add(comboBox);

		auto listRenderer = tgui::ListBoxRenderer(comboBox->getSharedRenderer()->getListBox());
		listRenderer.setBackgroundColor(sf::Color(61, 62, 63));
		listRenderer.setBackgroundColorHover(sf::Color(71, 72, 73));
		listRenderer.setSelectedBackgroundColor(sf::Color(81, 82, 83));
		listRenderer.setSelectedBackgroundColorHover(sf::Color(81, 82, 83));
		listRenderer.setSelectedTextColor(textColour);
		listRenderer.setTextColor(textColour);
		listRenderer.setTextColorHover(textColour);
		
		//panel->add(listRenderer);


		label = tgui::Label::create("Number of bars:");
		label->getRenderer()->setTextColor(textColour);
		label->setOrigin(0.5, 0.5);
		label->setPosition({ "50%","40%" });
		label->setTextSize(25);
		panel->add(label);

		auto editBox = tgui::EditBox::create();
		editBox->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		editBox->getRenderer()->setTextColor(textColour);
		editBox->getRenderer()->setCaretColor(sf::Color(200, 200, 200));
		editBox->getRenderer()->setCaretColorHover(sf::Color(200, 200, 200));
		editBox->getRenderer()->setBackgroundColorHover(sf::Color(70, 70, 70));
		editBox->setOrigin(0.5, 0.5);
		editBox->setPosition({ "50%","50%" });
		editBox->setTextSize(25);
		editBox->setSize({ "70%", "8%" });
		editBox->setDefaultText("0");
		panel->add(editBox,"EditBox");

		auto button = tgui::Button::create("Set");
		button->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		button->getRenderer()->setBackgroundColorHover(sf::Color(70, 70, 70));
		button->getRenderer()->setBackgroundColorDown(sf::Color(51, 51, 51));
		button->getRenderer()->setBackgroundColorDisabled(sf::Color(51, 51, 51));
		button->getRenderer()->setTextColor(textColour);
		button->getRenderer()->setTextColorDown(textColour);
		button->getRenderer()->setTextColorHover(sf::Color(textColour));
		button->getRenderer()->setBorderColorFocused(sf::Color(textColour));
		button->setSize({ "70%", "8%" });
		button->setOrigin(0.5, 0.5);
		button->setPosition({ "50%","70%" });
		button->setTextSize(25);
		panel->add(button);
		button->onPress(&Logic::setBar, this, std::ref(window), editBox);

		button = tgui::Button::create("Randomize");
		button->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		button->getRenderer()->setBackgroundColorHover(sf::Color(70, 70, 70));
		button->getRenderer()->setBackgroundColorDown(sf::Color(51, 51, 51));
		button->getRenderer()->setTextColor(textColour);
		button->getRenderer()->setTextColorDown(textColour);
		button->getRenderer()->setTextColorHover(sf::Color(textColour));
		button->getRenderer()->setBorderColorFocused(sf::Color(textColour));
		button->setSize({ "70%", "8%" });
		button->setOrigin(0.5, 0.5);
		button->setPosition({ "50%","80%" });
		button->setTextSize(25);
		panel->add(button);
		button->onPress(&Sort::randomize, &sort, std::ref(bars), std::ref(window), std::ref(gui));

		button = tgui::Button::create("Sort");
		button->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		button->getRenderer()->setBackgroundColorHover(sf::Color(70, 70, 70));
		button->getRenderer()->setBackgroundColorDown(sf::Color(51, 51, 51));
		button->getRenderer()->setBackgroundColorDisabled(sf::Color(51, 51, 51));
		button->getRenderer()->setTextColor(textColour);
		button->getRenderer()->setTextColorDown(textColour);
		button->getRenderer()->setTextColorHover(sf::Color(textColour));
		button->getRenderer()->setBorderColorFocused(sf::Color(textColour));
		button->setSize({ "70%", "8%" });
		button->setOrigin(0.5, 0.5);
		button->setPosition({ "50%","90%" });
		button->setTextSize(25);
		panel->add(button);
		button->onPress(&Logic::startSort,this, std::ref(bars), std::ref(window), std::ref(gui),comboBox);

		button = tgui::Button::create("Cancel");
		button->getRenderer()->setBackgroundColor(sf::Color(61, 62, 63));
		button->getRenderer()->setBackgroundColorHover(sf::Color(70, 70, 70));
		button->getRenderer()->setBackgroundColorDown(sf::Color(51, 51, 51));
		button->getRenderer()->setBackgroundColorDisabled(sf::Color(51, 51, 51));
		button->getRenderer()->setTextColor(textColour);
		button->getRenderer()->setTextColorDown(textColour);
		button->getRenderer()->setTextColorHover(sf::Color(textColour));
		button->getRenderer()->setBorderColorFocused(sf::Color(166, 167, 163));
		//button->getRenderer()->setTextColorDownDisabled(sf::Color());
		button->setSize({ "70%", "8%" });
		button->setOrigin(0.5, 0.5);
		button->setPosition({ "50%","90%" });
		button->setTextSize(25);
		button->setVisible(false);
		panel->add(button);
	}

	//Places the bar according to number specifed 
	void setBar(sf::RenderWindow& window, tgui::EditBox::Ptr number) {
		sf::RectangleShape bar;
		bars.clear();
		int numbers = number->getText().toInt();
		for (int i = 0; i < numbers; i++) {
			
			bar.setSize(sf::Vector2f(panelPos.x / float(numbers), -(windowSize.y * ((i + 1.f) / float(numbers)))));
			bars.push_back(sf::RectangleShape(bar));
			bars[i].setPosition(i * bar.getSize().x, windowSize.y);
		}
		this->update(window,gui,bars);

	}

	//starts the sort
	void startSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window,tgui::GuiSFML &gui, tgui::ComboBox::Ptr sorts) {
		if (bars.size() > 0 ) {
			switch (sorts->getSelectedItemIndex()) {
			case 0:
				sort.Bubble(bars, window, gui);
				break;
			case 1:
				sort.insertionSort(bars, window,gui);
				break;
			case 2:
				sort.mergeSort(bars, window,gui, 0, bars.size() - 1);
				break;
			case 3:
				sort.quickSort(bars, window,gui, 0, bars.size() - 1);
				break;
			}
		}
		
	}

	//update the window and gui
	void update(sf::RenderWindow& window, tgui::GuiSFML& gui,std::vector <sf::RectangleShape>& bars) {
		sf::Event event;
		while (window.pollEvent(event)) {

			gui.handleEvent(event);

			if (event.type == event.Closed)
				window.close();
		}
		//update
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			
		}
		toggle(window);
		//draw
		for (auto& i : bars) {
			window.draw(i);
		}
		gui.draw();
		window.display();
	}
	void toggle(sf::RenderWindow& window) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !buttonPressed) {
			if (!toggled) {

				setup(window);

				for (int i = 0; i < bars.size(); i++) {
					bars[i].setSize(sf::Vector2f(panelPos.x / float(bars.size()), bars[i].getSize().y));
					bars[i].setPosition(i * bars[i].getSize().x, windowSize.y);
				}
				toggled = true;
			}
			else {

				gui.removeAllWidgets();
				for (auto& i : bars) {
					for (int i = 0; i < bars.size(); i++) {
						bars[i].setSize(sf::Vector2f(windowSize.x / float(bars.size()), bars[i].getSize().y));
						bars[i].setPosition(i * bars[i].getSize().x, windowSize.y);
					}
				}
				toggled = false;
			}
			buttonPressed = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R) && buttonPressed) {
			buttonPressed = false;
		}
		
	}




};

int Sort::partition(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int start, int end) {
	Logic logic;

	int pivot = -bars[start].getSize().y;

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (-bars[i].getSize().y <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	//swap(arr[pivotIndex], arr[start]);
	swap(bars, pivotIndex, start);
	logic.update(window,gui,bars);

	// Sorting left and right parts of the pivot element
	int i = start;
	int j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (-bars[i].getSize().y <= pivot) {
			i++;
		}

		while (-bars[j].getSize().y > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			//swap(arr[i++], arr[j--]);	
			swap(bars, i++, j--);
			
		}
		logic.update(window, gui, bars);
	}

	return pivotIndex;
}
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void Sort::merge(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int const left, int const mid, int const right) {
	Logic logic;
	auto const subBarsOne = mid - left + 1;
	auto const subBarsTwo = right - mid;

	// Create temp arrays
/*	auto* leftArray = new int[subBarsOne],
		* rightArray = new int[subBarsTwo]*/;

		std::vector <sf::RectangleShape>leftBars;
		std::vector <sf::RectangleShape>rightBars;

		// Copy data to temp arrays leftArray[] and rightArray[]
		for (auto i = 0; i < subBarsOne; i++)
			leftBars.push_back(sf::RectangleShape(bars[left + i]));

		for (auto j = 0; j < subBarsTwo; j++)
			rightBars.push_back(sf::RectangleShape(bars[mid + 1 + j]));

		auto indexOfSubBarsOne = 0, // Initial index of first sub-array
			indexOfSubBarsTwo = 0; // Initial index of second sub-array
		int indexOfMergedVector = left; // Initial index of merged array

		// Merge the temp arrays back into array[left..right]
		while (indexOfSubBarsOne < subBarsOne && indexOfSubBarsTwo < subBarsTwo) {
			if (-leftBars[indexOfSubBarsOne].getSize().y <= -rightBars[indexOfSubBarsTwo].getSize().y) {
				bars[indexOfMergedVector].setSize(sf::Vector2f(leftBars[indexOfSubBarsOne].getSize().x,
					leftBars[indexOfSubBarsOne].getSize().y));
				indexOfSubBarsOne++;
			}
			else {
				bars[indexOfMergedVector].setSize(sf::Vector2f(rightBars[indexOfSubBarsTwo].getSize().x,
					rightBars[indexOfSubBarsTwo].getSize().y));
				indexOfSubBarsTwo++;
			}
			indexOfMergedVector++;
			logic.update(window, gui, bars);
		}
		// Copy the remaining elements of
		// left[], if there are any
		while (indexOfSubBarsOne < subBarsOne) {
			bars[indexOfMergedVector].setSize(sf::Vector2f(leftBars[indexOfSubBarsOne].getSize().x,
				leftBars[indexOfSubBarsOne].getSize().y));
			indexOfSubBarsOne++;
			indexOfMergedVector++;
			logic.update(window, gui, bars);
		}
		// Copy the remaining elements of
		// right[], if there are any
		while (indexOfSubBarsTwo < subBarsTwo) {
			bars[indexOfMergedVector].setSize(sf::Vector2f(rightBars[indexOfSubBarsTwo].getSize().x,
				rightBars[indexOfSubBarsTwo].getSize().y));
			indexOfSubBarsTwo++;
			indexOfMergedVector++;
			logic.update(window, gui, bars);
		}
}
void Sort::swap(std::vector <sf::RectangleShape>& bars, int i, int k) {
	sf::RectangleShape temp = bars[i];
	bars[i].setSize(sf::Vector2f(bars[k].getSize().x, bars[k].getSize().y));
	bars[k].setSize(sf::Vector2f(temp.getSize().x, temp.getSize().y));
}


void Sort::randomize(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui) {
	Logic logic;
	for (int i = bars.size() - 1; i > 0; i--){
		int j = rand() % (i + 1);
		swap(bars, i, j);
		logic.update(window,gui, bars);

	}
}

void Sort::Bubble(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui) {
	Logic logic;
	for (int i = 0; i < bars.size() - 1; i++) {

		for (int j = 0; j < bars.size() - i - 1; j++) {

			if (-bars[j].getSize().y > -bars[j + 1].getSize().y) {
				//swap(bars[j], bars[j + 1]);
				swap(bars, j, j + 1);

				logic.update(window,gui, bars);
			}

		}


	}
}

void Sort::insertionSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window,tgui::GuiSFML& gui) {
	int i, key, j;
	Logic logic;

	for (i = 1; i < bars.size(); i++)
	{
		key = -bars[i].getSize().y;
		j = i - 1;

		// Move elements of arr[0..i-1], 
		// that are greater than key, to one
		// position ahead of their
		// current position
		while (j >= 0 && -bars[j].getSize().y > key) {

			//swap(bars[j + 1], bars[j]);
			swap(bars, j + 1, j);
			logic.update(window, gui, bars);
			j = j - 1;
			
		}
		bars[j + 1].setSize(sf::Vector2f(bars[0].getSize().x, -key));

	}
}



// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void Sort::mergeSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int const begin, int const end) {
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(bars, window, gui, begin, mid);
	mergeSort(bars, window, gui, mid + 1, end);
	merge(bars, window, gui, begin, mid, end);
}



void Sort::quickSort(std::vector <sf::RectangleShape>& bars, sf::RenderWindow& window, tgui::GuiSFML& gui, int start, int end) {

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(bars, window,gui, start, end);

	// Sorting the left part
	quickSort(bars, window, gui, start, p - 1);

	// Sorting the right part
	quickSort(bars, window, gui, p + 1, end);
}


int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Sorting visual", sf::Style::Close);

	Logic logic(window);
	
	while (window.isOpen()) {
		logic.update(window,logic.gui,logic.bars);
	}
}