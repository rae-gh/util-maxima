#!/usr/bin/env python3
"""
Author:    Rachel Alcraft
Date:      26/08/2021
Function:  A CGI file to take text and run an external C++ file
Description: 
============

"""

#************************************************************************************************

import cgi
import Maxima
import PhdWebBuilder as pwb


# Useful debugging output
import cgitb
cgitb.enable()  # Send errors to browser
# cgitb.enable(display=0, logdir="/path/to/logdir") # log errors to a file

# Print the HTML MIME-TYPE header
print ("Content-Type: text/html\n")

pdb = '1ejg'
asCSV = True
username = ""
password = ""
form = cgi.FieldStorage()
if 'dataInput' in form:
  pdb = str(form["dataInput"].value)
if 'format' in form:  
  asCSV = "asCsv"== str(form["format"].value)
if 'email' in form:  
  username = str(form["email"].value)
if 'password' in form:  
  password = str(form["password"].value)
  

access = pwb.userSuccess(username,password)
html = pwb.getHeader()
html += pwb.getBodyA(pdb,asCSV,username,password)
if access:
  done = Maxima.doWeHaveAllFiles(pdb)
  data = Maxima.runCppModule(pdb)
  html += pwb.getBodyB(pdb,data,asCSV)
  html += pwb.getBodyC(pdb,0,0,0,0,0,0,0,0,0)
  #html += pwb.getBodyD(pdb,data)
else:
  html += "<h2>!!No access!! Enter a valid email address.</h2>"

html += pwb.getFooter()

print(html)

#************************************************************************************************
