/*
    tkr
    Calculation of turbocharger parameters.

    File: auxfunctions.cpp

    Copyright (C) 2014 Artem Petrov <pa2311@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "auxfunctions.hpp"
#include "constants.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using std::string;
using std::vector;
using std::cout;
using std::ifstream;

vector< vector<double> > srcData() {

    vector< vector<string> > raw;
    vector< vector<double> > srcdata;

    const boost::filesystem::path file(SRCDATAFILE);

    if ( !boost::filesystem::exists(file) ) {
        cout << ERRORMSGBLANK << "Source data file \"" << SRCDATAFILE << "\" not found!\n";
        return srcdata;
    }

    ifstream fin(SRCDATAFILE);

    if ( !fin ) {
        cout << ERRORMSGBLANK << "Can not open file \"" << SRCDATAFILE << "\" to read!\n";
        return srcdata;
    }

    while ( !fin.eof() ) {

        string s;
        vector<string> elem;

        getline(fin, s);

        if ( !s.empty() ) {

            boost::split(elem, s, boost::is_any_of(CSVDELIMETER));
            bool valid_str = true;

            for ( size_t i=0; i<elem.size(); i++ ) {
                if ( elem[i].empty() ) {
                    valid_str = false;
                    break;
                }
            }

            if ( valid_str ) {
                raw.push_back(elem);
            }
        }
    }

    if ( raw.size() < (TABLECAPSTRNUM + 1) ) {
        cout << ERRORMSGBLANK << "No source data (\n";
        return srcdata;
    }

    for ( size_t i=TABLECAPSTRNUM; i<raw.size(); i++ ) {

        if ( raw[i].size() != colCaptions.size() ) {
            cout << WARNMSGBLANK << "Row " << i << " of source data array has wrong elements number! Skipped.\n";
            continue;
        }

        vector<double> elem;

        for ( size_t j=0; j<raw[i].size(); j++ ) {
            elem.push_back(boost::lexical_cast<double>(raw[i][j]));
        }

        srcdata.push_back(elem);
    }

    fin.close();

    return srcdata;
}

string trimDate(const string &str) {

    if ( str.size() == 1 ) {
        return "0" + str;
    }
    else if ( str.size() == 2 ) {
        return str;
    }

    return "00";
}
