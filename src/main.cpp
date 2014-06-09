/*
    tkr
    Calculation of turbocharger parameters.

    File: main.cpp

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

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "configuration.hpp"
#include "identification.hpp"
#include "constants.hpp"
#include "auxfunctions.hpp"
#include "tkrparameters.hpp"

using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::vector;
using std::cout;
using std::cin;

int main() {

    cout << "\n\t" << Identification{}.name() << " v" << Identification{}.version() << "\n"
         << "\t" << Identification{}.description() << "\n\n"
         << "Copyright (C) " << Identification{}.copyrightYears() << " " << Identification{}.authors() << "\n\n"
         << Identification{}.licenseInformation() << "\n\n";

    shared_ptr<Configuration> conf(new Configuration());
    conf->readConfigFile();

    vector< vector<double> > srcdata = srcData();

    unique_ptr<TkrParameters> tkr(new TkrParameters(conf));
    
    if ( tkr->calculate(srcdata) ) {
        tkr->createReport();
    }
    else {
        cout << ERRORMSGBLANK << "Calculation failed!\n";
    }

    cout << "\n\nPress any key to exit...";
    cin.get();

    return 0;
}
