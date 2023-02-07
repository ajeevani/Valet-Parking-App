#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Menu.h"

using namespace std;

namespace valetpark
{
	MenuItem::MenuItem(const char* str)
	{
		if (str)
		{
			strcpy(m_char, str);
		}
		else
		{
			setEmpty();
		}
	}
	MenuItem::operator bool() const
	{
		return m_char[0] != char(0);
	}
	void MenuItem::display(int indent, int select)
	{
		for (int i = 0; i < (indent * 4); i++)
		{
			cout << " ";
		}
		cout << select << "- " << m_char << endl;
	}
	void MenuItem::setEmpty()
	{
		m_char[0] = char(0);
	}
	Menu::Menu(const char* title, int indent)
	{
		if (title != nullptr)
		{
			setTitle(title);
			if (indent > 0)
			{
				m_spaceindent = indent;
			}
		}
		else
		{
			setEmpty();
		}
	}
	Menu::~Menu()
	{
		setEmpty();
	}
	void Menu::setEmpty()
	{
		m_title[0] = char(0);
		m_spaceindent = 0;
		for (int i = 0; i < m_items; i++)
		{
			delete m_menuitem[i];
			m_menuitem[i] = nullptr;
		}
		m_items = 0;
	}
	void Menu::setTitle(const char* title)
	{
		if (strlen(title) >= 50)
		{
			strcpy(m_title, title);
		}
		else
		{
			for (int i = 0; i < 50; i++)
			{
				m_title[i] = title[i];
			}
		}
	}
	Menu::operator bool() const
	{
		return m_title[0] != char(0);
	}
	bool Menu::isEmpty() const
	{
		return m_title[0] == char(0);
	}
	void Menu::indent() const
	{
		for (int i = 0; i < (m_spaceindent * 4); i++)
		{
			cout << " ";
		}
	}
	void Menu::display() const
	{
		int i;
		if(!isEmpty())
		{
			indent();
			cout << m_title << endl;
			if (m_items > 0)
			{
				for (i = 0; i < m_items; i++)
				{
					m_menuitem[i]->display(m_spaceindent, i+1);
				}
				indent();
				cout << "> ";
			}
			else
			{
				cout << "No Items to display!" << endl;
			}
		}
		else
		{
			cout << "Invalid Menu!" << endl;
		}
	}
	Menu& Menu::operator=(const char* title)
	{
		setEmpty();
		if(title != nullptr)
		{
			setTitle(title);
		}
		return *this;
	}
	void Menu::add(const char* item)
	{
		if(item != nullptr)
		{
			if (!isEmpty() && (m_items <= MAX_NO_OF_ITEMS))
			{
				MenuItem* temp = new MenuItem(item);
				m_menuitem[m_items] = temp;
				m_items++;
			}
		}
		else
		{
			setEmpty();
		}
	}

	void Menu::clear()
	{
		for (int i = 0; i < m_items; i++)
		{
			delete m_menuitem[i];
			m_menuitem[i] = nullptr;
		}
	}

	Menu& Menu::operator<<(const char* item)
	{
		add(item);
		return *this;
	}

	int Menu::run() const
	{
		int select = 0;
		bool pass = false;
		display();
		if (m_items <= 0)
		{
			return 0;
		}
		while (!pass)
		{
			cin >> select;
			if(cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Integer, try again: ";
			}
			else if(select < 1 || select > m_items)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid selection, try again: ";
			}
			else
			{
				pass = true;
				cin.ignore(1000, '\n');
			}
		}
		return select;
	}

	Menu::operator int() const
	{
		return run();
	}
}