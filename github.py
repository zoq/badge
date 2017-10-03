#/usr/bin/python

"""
@file github.py
@author Marcus Edel
Implementation of the github/travis routine.
"""

import usb # 1.0 not 0.4
import sys, time, urllib2, re

sys.path.append("..")
from arduino.usbdevice import ArduinoUsbDevice

github = "mlpack/mlpack"
travis = "mlpack"
branch = "master"
project = "mlpack"

if __name__ == "__main__":
    try:
        theDevice = ArduinoUsbDevice(idVendor=0x16c0, idProduct=0x05df)

        print "Found: 0x%04x 0x%04x %s %s" % (theDevice.idVendor,
                                              theDevice.idProduct,
                                              theDevice.productName,
                                              theDevice.manufacturer)
    except:
        pass

    # Get travis build status.
    travisURL = "https://api.travis-ci.org/%s/%s.svg?branch=%s" % (travis,
                                                                   travis,
                                                                   branch)
    content = urllib2.urlopen(travisURL).read()

    if "passing" in content:
        buildStatus = "passing"
    elif "failing" in content:
        buildStatus = "failing"
    elif "error" in content:
        buildStatus = "error"
    elif "no build available" in content:
        buildStatus = "no build available"
    elif "unknown" in content:
        buildStatus = "unknown"

    # Get Github informations.
    githubURL = "https://api.github.com/repos/%s" % (github)
    content = urllib2.urlopen(githubURL).read()

    stargazers = re.search('.*stargazers_count":(\d+),.*', content)
    stargazersCount = 0
    if stargazers:
        stargazersCount = stargazers.group(1)

    issues = re.search('.*open_issues_count":(\d+),.*', content)
    issuesCount = 0
    if issues:
        issuesCount = issues.group(1)

    # MLPACK - BUILD > PASSING < ISSUES > 123 < STARS - 244
    data = project.upper() + ">" + buildStatus.upper() + "<s" + \
        str(issuesCount).upper() + "i" + stargazersCount + ""

    for c in data:
        theDevice.write(ord(c))
        time.sleep(0.1)
