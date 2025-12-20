#pragma once
#include "clsUser.h"

clsUser ActiveUser = clsUser::Find("", "");
/*
Dummy Function to create an empty User object
without using the constructor of the object.

Find ("", "") returns an empty object when
it checks for the Username, Password.
*/