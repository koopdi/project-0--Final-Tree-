/**
 * @file Workspace.cpp
 * @author Andrew Hanson, Christen Spadevechia, Travis McKinney
 */

#include "Workspace.h"

#include <iostream>
#include <string>

Workspace::Workspace() : workspaceID((long long)(this))
{
	using namespace std;
	tree = new WindowTree(this);
	if (tree == nullptr)
	{
		cout << "tree is null" << endl;
		throw "Workspace: cannot add to null tree"s;
	}
}

bool Workspace::operator<(Workspace& other)
{
	return workspaceID < other.workspaceID;
}

bool operator<(std::shared_ptr<Workspace>& a, std::shared_ptr<Workspace>& b)
{
	return (*a) < (*b);
}

int Workspace::getHeight() const { return height; }

int Workspace::getWidth() const { return width; }

Point Workspace::getPosition() const { return position; }

int Workspace::getNumWindows() const { return numWindows; }

void Workspace::setHeight(int height) { this->height = height; }

void Workspace::setWidth(int width) { this->width = width; }

void Workspace::setPosition(Point position) { this->position = position; }

bool Workspace::addWindow(bool partVertically, int windowID, double part1Size)
{
	using namespace std;
	cout << "In method workspace::addWindow." << endl;
	if (tree == nullptr)
	{
		cout << "tree is null" << endl;
		throw "Workspace: cannot add to null tree"s;
	}
	bool success = tree->add(partVertically, part1Size, windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map[windowID];
	// }
	return success;
}

bool Workspace::removeWindow(int windowID)
{
	bool success = tree->remove(windowID);
	// if (success) {
	//		TODO: add to map<windowID:set<workspaceID>>
	//		map.erase(windowID);
	// }
	return success;
}