"""
Copyright (c) 2014, Casper Steinmann <casper.steinmann@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
"""

# This script generates different fade-in and fade-out functions
# and dumps the result in C arrays.

import numpy
import math

# evaluation region
minx = 0.0
maxx = 5.0
delta = 0.1

# constants used in the formulas. see specific formulas for precise use.
fd_a = 4.0
fd_b = (maxx-minx) / 2.0
cos_a = maxx - minx
lin_a = cos_a

# print format for numbers
floatformat = "{0:6.3f}f,"


X = numpy.arange(minx, maxx+delta, delta)

#
def printfunc(f):
    name, values = f()
    snam = "float {0}[{1}]".format(name, "FADERSTEPS")
    sval = ""
    for value in values:
        sval = sval + floatformat.format(value)

    print("{0:25s} = {{{1}}};".format(snam, sval[:-1]));

#
# FERMI-DIRAC
#
# fade-in
# 1 / (exp(-a(x-b))+1)
def fi_fermidirac():
    return "FI_FERMIDIRAC", 1/(numpy.exp(-fd_a*(X-fd_b))+1)

# fade-out
# 1 / (exp(a(x-b))+1)
def fo_fermidirac():
    return "FO_FERMIDIRAC", 1/(numpy.exp( fd_a*(X-fd_b))+1)

# 
# COS
#
# fade-in
# 0.5*(1+cos((x-a)*pi/a))
def fi_cos():
    return "FI_COS", 0.5*(1+numpy.cos((X-cos_a)*numpy.pi/cos_a))

# fade-out
# 0.5*(1+cos(x*pi/a))
def fo_cos():
    return "FO_COS", 0.5*(1+numpy.cos(X*numpy.pi/cos_a))

#
# Linear
#
# fade-in
#
def fi_lin():
    return "FI_LIN", X/lin_a

def fo_lin():
    return "FO_LIN", 1-X/lin_a

print "#ifndef __FADERS_H_"
print "#define __FADERS_H_"
print "#define FADERSTEPS %i" % len(X);
printfunc( fi_fermidirac )
printfunc( fo_fermidirac )
printfunc( fi_cos )
printfunc( fo_cos )
printfunc( fi_lin )
printfunc( fo_lin )
print "#endif"
