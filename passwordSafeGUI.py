# encoding=utf8
############################################################
# A simple Password Safe for my own purposes. 
# This is the launching point for the program
# hosting the GUI
#############################################################

from subprocess import Popen # To call my C++ authentication
import PySimpleGUI as sg # For the GUI

FILENAME = "logins.txt"

# For updating a line:
def updatePassword(line, change_pass):
    # Read the File, get the correct line
    contents = readFile()
    line_index = contents.index(line)

    # Split the line to change the pass
    string_list = contents[line_index].split()

    print(string_list)

    # location of old_pass in the file
    old_pass = string_list[2]

    # Replace the password
    contents[line_index] = contents[line_index].replace(old_pass, change_pass)

    # Write changes to file
    writeFile(contents)

# Completely forget a line in the .txt file
def deleteEntry(line):
    contents = readFile()
    contents.remove(line)
    writeFile(contents)

# Reads the file, returns a list of the lines as strings
def readFile():
    f = open(FILENAME, "r")
    contents = f.readlines()
    f.close()
    return contents

# Deletes and overwrites the file with new contents
def writeFile(contents):
    f = open(FILENAME, "w")
    f.writelines(contents)
    f.close()


# Add a new line to the text file
def addEntry(username, password, website):

    # Open the file for appending a new line
    f = open(FILENAME, "a")
    contents = username + " "

    # Get the Salt, needed if put on a client server
    p = Popen(['PasswordSafe.exe', '3', 'none'])
    response = p.wait()
    
    # turn the salt into a string
    salt = str(response)

    # Build the line and add it
    contents = contents + salt + " "
    contents = contents + password + " " + website + '\n'
    f.write(contents)

# Change the authentication password to enter the application
def updateMasterPassword(new_pass, old_pass):
    # Change through C++ implementations
    p = Popen(['PasswordSafe.exe', '1', old_pass, new_pass])
    response = p.wait()
    # 0 is a fail, 1 is a success
    return response

# Build the GUI using PySimpleGUI

# The login window, along with a way to read the values
event, values = sg.Window('Authentication',
                  [[sg.T('Enter your Password'), sg.In(key='-PASS-')],
                  [sg.B('Submit'), sg.B('Cancel') ]]).read(close=True)

password = values['-PASS-']

# Authenticate through C++ implementations
p = Popen(['PasswordSafe.exe', '0', password])
response = p.wait()

# A zero means a failure, a one means success
if response == 0:
    quit()

# Create a new window
# Layout must be dynamic based on file-length
layout = [[sg.Listbox(values=readFile(), size=(70, 20),
key='lines', select_mode="LISTBOX_SELECT_MODE_SINGLE")],
[sg.B("Add New Entry"), sg.B("Update Password"), 
sg.B("Change Master Password"), sg.B("Delete Entry")]]

# Make the master window

Window = sg.Window('Password Safe', layout)

# Create an event loop
while True:
    event, values = Window.read()
    
    # Handle the various events
    if event == "Add New Entry":
        # Popup for new entry
        event, values = sg.Window('Add New Entry',
        [[sg.T('Enter Username'), sg.In(key='-USER-')],
        [sg.T('Enter Password'), sg.In(key='-ENTRY_PASS-')],
        [sg.T('Enter Website'), sg.In(key='-SITE-')],
        [sg.B('Submit'), sg.B('Cancel') ]]).read(close=True)

        # Handle the Cancel
        cancelled = False
        if event == 'Cancel':
            cancelled = True
            
        if (not cancelled):
            # Set the new variables
            user = values['-USER-']
            entry_pass = values['-ENTRY_PASS-']
            site = values['-SITE-']

            # Add it to the file
            addEntry(user, entry_pass, site)

            # Update the listbox
            Window.FindElement('lines').Update(values=readFile())

    # Update an entry password
    if event == "Update Password":
        # Get the line content
        line = values['lines']

        # Make a popup to accept a new password
        event, values = sg.Window('Change Entry Password',
                  [[sg.T('Enter your new Password'), sg.In(key='-NEW_PASS-')],
                  [sg.B('Submit'), sg.B('Cancel') ]]).read(close=True)

        # Handle the Cancel
        cancelled = False
        if event == 'Cancel':
            cancelled = True
            
        if (not cancelled):
            # Read new value from the popup window, send it off
            new_pass = values['-NEW_PASS-']

            # Send it off
            updatePassword(line[0], new_pass)

            # Update the listbox
            Window.FindElement('lines').Update(values=readFile())
    
    # The user decides to change the Master Password
    if event == "Change Master Password":
        # C++ Authentication after a pop-up window
        # for user input of new password
        event, values = sg.Window('Change Master Password',
                  [[sg.T('Enter your new Password'), sg.In(key='-NEW_PASS-')],
                  [sg.B('Submit'), sg.B('Cancel') ]]).read(close=True)

        # Handle the Cancel
        cancelled = False
        if event == 'Cancel':
            cancelled = True
            
        if (not cancelled):
            # Read new value from the popup window, send it off
            new_pass = values['-NEW_PASS-']
            response = updateMasterPassword(new_pass, password)

            # Set up the text message
            text = "Failed to Update Password"
            if(response):
                text = "Password Updated Successfully"
                password = new_pass

            # Popup window for success or failure
            event, values = sg.Window('Password Change',
            [[sg.T(text)], [sg.B('OK')]]).read(close=True)

    if event == "Delete Entry":
        # Get the line content
        line = values['lines']

        # Delete the selected item
        deleteEntry(line[0])

        # Update the listbox
        Window.FindElement('lines').Update(values=readFile())

    # End program if user closes window, encrypt file
    if event == sg.WIN_CLOSED:
        p = Popen(['PasswordSafe.exe', '2', password])
        p.wait()
        break