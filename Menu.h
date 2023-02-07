#ifndef VALETPARK_MENU_H_
#define VALETPARK_MENU_H_
namespace valetpark {

	const int MAX_NO_OF_ITEMS = 10;

	class MenuItem
	{
		friend class Menu;
	private:
		char m_char[51]{};

		MenuItem() = default;
		MenuItem(const char* str);
		MenuItem(const MenuItem&) = delete;
		~MenuItem() = default;
		MenuItem& operator=(const MenuItem&) = delete;
		operator bool() const;
		void display(int indent, int select);
		void setEmpty();
	};

	class Menu : public MenuItem
	{
		char m_title[51]{};
		MenuItem *m_menuitem[MAX_NO_OF_ITEMS];
		int m_spaceindent = 0;
		int m_items = 0;
	public:
		Menu() = default;
		Menu(const char* title, int indent = 0);
		Menu(const Menu&) = delete;
		~Menu();
		Menu& operator=(const Menu&) = delete;
		void setEmpty(); // sets title to '\0'
		void setTitle(const char* title); // sets title to parameter (only first 50)
		operator bool()const;
		bool isEmpty() const;
		void indent() const;
		void display() const;
		Menu& operator=(const char* title);
		void add(const char* item);
		void clear();
		Menu& operator<<(const char* item);
		int run() const;
		operator int() const;
	};

}
#endif // !