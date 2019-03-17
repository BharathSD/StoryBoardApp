#pragma once
#include"StoryBoard.h"
#include <map>
#include <iostream>

class StoryBoardApp
{
	std::map<std::string, CStoryBoard*> m_StoryBoardlist;
public:
	StoryBoardApp()
	{
	}

	~StoryBoardApp()
	{
		for (auto eachStoryBoard : m_StoryBoardlist)
			delete eachStoryBoard.second;
	}

	void createStoryBoard(std::string storyBoardName)
	{
		if (m_StoryBoardlist.find(storyBoardName) == m_StoryBoardlist.end())
		{
			// the story board doesn't exist
			m_StoryBoardlist[storyBoardName] = new CStoryBoard(storyBoardName);
		}
	}

	template<typename... Args>
	void addNote(std::string storyBoardName, std::string noteTitle,
		std::string noteTextConent, Args... tags)
	{
		m_StoryBoardlist[storyBoardName]->addNote(noteTitle, noteTextConent, tags...);
	}

	void deleteNote(std::string storyBoardName, std::string noteTitle)
	{
		m_StoryBoardlist[storyBoardName]->deleteNote(noteTitle);
	}

	void searchByTitle(std::string storyBoardName, std::string noteTitle)
	{
		std::cout << "Searching in " << storyBoardName << " for note " << noteTitle << std::endl;
		if (m_StoryBoardlist.find(storyBoardName) != m_StoryBoardlist.end())
		{
			// story board exists
			std::cout << m_StoryBoardlist[storyBoardName]->searchByTitle(noteTitle) << std::endl;
		}
	}

	void searchByText(std::string storyBoardName, std::string noteText)
	{
		std::cout << "Searching in " << storyBoardName << " containing note text " << noteText << std::endl;
		if (m_StoryBoardlist.find(storyBoardName) != m_StoryBoardlist.end())
		{
			// story board exists
			std::cout << m_StoryBoardlist[storyBoardName]->searchByText(noteText) << std::endl;
		}
	}

	void searchByTag(std::string storyBoardName, std::list<std::string> tags)
	{
		std::cout << "Searching in " << storyBoardName << " containing note with tags ";
		for (auto tag : tags)
			std::cout << tag << ", ";
		std::cout << std::endl;
		if (m_StoryBoardlist.find(storyBoardName) != m_StoryBoardlist.end())
		{
			// story board exists
			std::cout << m_StoryBoardlist[storyBoardName]->searchByTag(tags) << std::endl;
		}
	}

	void display(std::string storyBoardName)
	{
		if (m_StoryBoardlist.find(storyBoardName) != m_StoryBoardlist.end())
		{
			// story board exists
			std::cout << *(static_cast<CStoryBoard*>(m_StoryBoardlist[storyBoardName])) << std::endl;
		}
		
	}
};