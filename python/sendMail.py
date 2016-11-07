#!/usr/bin/python

import smtplib

sender = 'sender@mail.it'
receivers = ['receiver@mail.it']

message = """From: Sender <sender@mail.it>
To: Receiver <receiver@mail.it>
Subject: subject of mail

Body of mail.
"""

try:
    smtpObj = smtplib.SMTP_SSL('smtp.mail.it', 465)
    smtpObj.login('login', 'password')
    smtpObj.sendmail(sender, receivers, message)         
    print("Successfully sent email")
except SMTPException:
    print("Error: unable to send email")


