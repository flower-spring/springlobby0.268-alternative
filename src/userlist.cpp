/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

/**
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

TODO: remove all wx stuff & merge / move to

lsl/container/userlist.cpp

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**/
#include "userlist.h"

#include <wx/log.h>
#include <iterator>
#include <stdexcept>

#include "log.h"
#include "user.h"
#include "utils/conversion.h"

const UserList::user_map_t::size_type SEEKPOS_INVALID = UserList::user_map_t::size_type(-1);

UserList::UserList()
    : m_seek(m_users.end())
    , m_seekpos(SEEKPOS_INVALID)
{
}

UserList::~UserList()
{
	m_seek = m_users.end();
	m_seekpos = SEEKPOS_INVALID;
}

void UserList::AddUser(User& user)
{
	m_users[user.GetNick()] = &user;
	m_seekpos = SEEKPOS_INVALID;
}

void UserList::RemoveUser(const std::string& nick)
{
	m_users.erase(nick);
	m_seekpos = SEEKPOS_INVALID;
}

User& UserList::GetUser(const std::string& nick) const
{
	user_const_iter_t u = m_users.find(nick);
	// user doesn't exist -> throw excpetion (else it will crash/invalid mem access / bad things will happen! in the next line)
	ASSERT_EXCEPTION(u != m_users.end(), _T("UserList::GetUser(\"") + TowxString(nick) + _T("\"): no such user"));
	assert(u != m_users.end());
	return *u->second;
}

User& UserList::GetUser(user_map_t::size_type index) const
{
	if ((m_seekpos == SEEKPOS_INVALID) || (m_seekpos > index)) {
		m_seek = m_users.begin();
		m_seekpos = 0;
	}
	std::advance(m_seek, index - m_seekpos);
	m_seekpos = index;
	return *m_seek->second;
}

bool UserList::UserExists(std::string const& nick) const
{
	return m_users.find(nick) != m_users.end();
}

UserList::user_map_t::size_type UserList::GetNumUsers() const
{
	return m_users.size();
}

void UserList::Nullify()
{
	for (user_map_t::iterator it = m_users.begin(); it != m_users.begin(); ++it) {
		delete it->second;
		it->second = NULL;
	}
}
