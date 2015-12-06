#pragma once

#include <cstdbool>
#include <string>
#include <cctype>

using std::string;

/*
this function is for answer for C comment, if it
is a C comment, it will return true, otherwise false;
It does not support for nested comment yet.

*/
bool scan_c_comment(string r_str);

/*
 this is extension of scan_c_comment, which can hanle nested C-style comment
 below is the dot code, you can see the graph by excute them:

 digraph G {

 1->2 [label = "/"];

 2->3 [label = "*"];

 3->5 [label = "/"];
 3->3 [label = "other"];
 3->4 [label = "*"]

 4->7 [label = "/"];
 4->4 [label = "*"];
 4->3 [label = "other"];

 5->6 [label = "*"];
 5->3 [label = "other"];

 6->5 [label = "/"];
 6->6 [label = "other"];
 6->4 [label = "*"];

 7->8 [label = "other"];

 8->9 [label = "/"];
 8->4 [label = "*"];

 9->3 [label = "*"];
 9->8 [label = "other"];

 }

*/
bool ex_scan_c_comment(string r_str);
void test_scan_commnet();