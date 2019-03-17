#pragma once
#include <sstream>
#include "Notes.h"

class CStoryBoard
{
private:
	std::list<CNotes*> m_NoteList;
	std::string m_name;

	bool checkIfNoteisPresent(std::string title)
	{
		bool retVal(false);
		for (std::list<CNotes*>::iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			if (**itr == title)
			{
				// already exists
				retVal = true;
				break;
			}
		}
		return retVal;
	}

	std::string str() const
	{
		std::stringstream ss;

		ss << "\t\t\t\t" << "Story Board : " << m_name << std::endl;
		int counter(0);
		for (std::list<CNotes*>::const_iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			ss << "Note - " << ++counter << std::endl;
			ss << **itr << std::endl;
		}
		return ss.str();
	}

	CNotes* searchNotesByTitle(std::string title)
	{
		// title is considered unique, hence the return type of the function isjust a pointer type
		CNotes* pData = nullptr;
		for (std::list<CNotes*>::iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			if (**itr == title)
			{
				pData = *itr;
			}
		}
		return pData;
	}

	std::list<CNotes*> searchNotesByTag(std::list<std::string> tags)
	{
		std::list<CNotes*> filteredNotesData;
		for (std::list<CNotes*>::iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			if (**itr == tags)
			{
				filteredNotesData.push_back(*itr);
			}
		}
		return filteredNotesData;
	}

	std::list<CNotes*> searchNotesByText(std::string textContent)
	{
		std::list<CNotes*> filteredNotesData;
		for (std::list<CNotes*>::iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			if ((*itr)->compareText(textContent))
			{
				filteredNotesData.push_back(*itr);
			}
		}
		return filteredNotesData;
	}
public:

	CStoryBoard(std::string name) :m_name(name)
	{
	}

	~CStoryBoard()
	{
		for (auto note : m_NoteList)
		{
			if (note)
				delete note;
		}
		m_NoteList.clear();
	}

	template<typename... Args>
	void addNote(std::string title, std::string textContent, Args... tags)
	{
		if(!checkIfNoteisPresent(title)) // check if note already exists
			m_NoteList.push_back(new CNotes(title, textContent, tags...));

		// todo throw exceptions if the Note already exists
	}

	void deleteNote(std::string title)
	{
		for (std::list<CNotes*>::iterator itr = m_NoteList.begin(); itr != m_NoteList.end(); ++itr)
		{
			if (**itr == title)
			{
				// found the match
				delete *itr;
				m_NoteList.erase(itr);
				break;	// title is unique, hence there would be only one Note with the title name
			}
		}
	}

	
	std::string searchByTitle(std::string title)
	{
		CNotes* pNote = searchNotesByTitle(title);

		std::stringstream ss;

		ss << "Search Result : " << std::endl;
		ss << *pNote << std::endl;

		return ss.str();
	}

	std::string searchByTag(std::list<std::string> tags)
	{
		auto notesList = searchNotesByTag(tags);

		std::stringstream ss;

		ss << "Search Result : " << std::endl;
		for(auto note : notesList)
			ss << *note << std::endl;

		return ss.str();
	}

	std::string searchByText(std::string textContent)
	{
		auto notesList = searchNotesByText(textContent);

		std::stringstream ss;

		ss << "Search Result : " << std::endl;
		for (auto note : notesList)
			ss << *note << std::endl;

		return ss.str();
	}

	friend std::ostream &operator<<(std::ostream &os, const CStoryBoard &storyBoard);
};

std::ostream &operator<<(std::ostream &os, const CStoryBoard &storyBoard)
{
	os << storyBoard.str() << std::endl;
	return os;
}