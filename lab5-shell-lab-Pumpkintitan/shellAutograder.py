from __future__ import print_function
import subprocess
import sys
import time
import re
import io

testNumber = 10

##
## This test framework had some problems for test11, test12 and test13 of the standard
## assignment. The following subprocess.Popen runs the jobs, but does not read
## all the input and some processes are left around such that when the second test
## is running, those processes would appear in the 'ps' output.
##
## I've changed the solution to read the full input and place it into a string
## buffer before running the second test. This removes this minor glitch.
##
## dirk

def runCmd(cmd): 
    proc = subprocess.Popen(cmd, bufsize=1, text=True, stdout=subprocess.PIPE)
    try:
        stdout, stderr = proc.communicate(timeout=10)
    except subprocess.TimeoutExpired:
        proc.kill()
        stdout, stderr = proc.communicate()
    return stdout, stderr

def runTrace(testNumber):
    success=True
    test_out, test_err = runCmd(["make", "test%02d"%(testNumber)])
    ref_out, ref_err = runCmd(["make", "rtest%02d"%(testNumber)])

    test=io.StringIO(test_out)
    ref=io.StringIO(ref_out)

    testLine = test.readline()
    refLine = ref.readline()
    if (testLine.strip() != './sdriver.pl -t trace%02d.txt -s ./tsh -a "-p"'%(testNumber)):
        print("\tERROR: Bad first line in test.")
        success=False
    refLine = ref.readline()
    testLine = test.readline()
    while((testLine != "") or (refLine != "")):
        if refLine.strip() == "tsh> /bin/ps a":
            if testLine.strip() != refLine.strip():
                print("\tERROR: \"%s\" <=!=> \"%s\""%(refLine.strip(),
                                                    testLine.strip()))
                success = False
            success =  psScan(ref, test) and success
        success = normalScan(refLine, testLine) and success
        testLine = test.readline()
        refLine = ref.readline()
    return success

def normalScan(refL, testL):
    if refL == "":
        print("\tERROR: Test too short.")
        return False
    elif testL == "":
        print("\tERROR: Test too long.")
        return False
    elif testL != refL:
        noPIDtest = re.sub(r'\([0-9]+\)*', '(*PID*)', testL)
        noPIDref = re.sub(r'\([0-9]+\)*', '(*PID*)', refL)
        if(noPIDtest != noPIDref):
            print("\t\"%s\" <=!=> \"%s\""%(noPIDtest.strip(), noPIDref.strip()))
            return False

    return True

def isProgramWeCareAbout(line):
    if "/bin/sh" in line or "/usr/bin/perl" in line:
        return False

    if "./mysplit " in line \
       or "./myspin " in line \
       or "./myint "in line \
       or "./mystop " in line \
       or "./tsh " in line:
        return True
    else:
        return False


def psScan(ref, test):
    success=True
    #Dict stores state, and number of lines like this we saw, for each cmd.
    refDict = {}
    testDict = {}

    #Collect ref info.
    refL = ref.readline()
    psRefHeader = refL.strip()
    refL = ref.readline()
    while(("tsh>" not in refL) and refL!=""):
        psLine = refL.strip().split(None, 4)
        if isProgramWeCareAbout(psLine[4]):
            if psLine[4] in refDict:
                refDict[psLine[4]].append(psLine[2])
            else:
                refDict[psLine[4]] = [psLine[2]]
        refL = ref.readline()
    
    #Collect test info.
    testL = test.readline()
    if(testL.strip()!=psRefHeader):
        print("\tERROR: Unexpected ps header in test.")
        success=False
    testL = test.readline()
    while(("tsh>" not in testL) and testL!=""):
        psLine = testL.strip().split(None, 4)
        if isProgramWeCareAbout(psLine[4]):
            if psLine[4] in testDict:
                testDict[psLine[4]].append(psLine[2])
            else:
                testDict[psLine[4]] = [psLine[2]]
        testL = test.readline()
    #Now, comparing the two dicts.
    for key in refDict.keys():
        try:
            if(refDict[key] != testDict[key]):
                print("\tERROR: Status for (%s) does not match:"%(key))
                print("\t\tReference Statuses: %s"%(refDict[key]))
                print("\t\tYour Statuses: %s"%(testDict[key]))
                success = False
        except KeyError:
            if "./tshref" in key:
                continue
            print("\tERROR: \"%s\" not found in test dict."%(key))
            success = False
            
    return success

if len(sys.argv) > 1:
    for trace in sys.argv[1:]:
        i = int(trace)
        print("Running trace %02d..."%(i))
        if runTrace(i):
            print("\tPassed.")
        else:
            print("\tFailed.")
else:
    numPassed = 0
    for i in range(16):
        print("Running trace %02d..."%(i+1))
        if runTrace(i+1):
            numPassed+=1
            print("\tPassed.")
        else:
            print("\tFailed.")

    print("Total Passed: %d/16\tGrade: "%(numPassed),end="")
    if(numPassed>13):
        print("100%")
    elif(numPassed>10):
        print("90%")
    elif(numPassed>8):
        print("80%")
    elif(numPassed>5):
        print("60%")
    elif(numPassed>3):
        print("30%")
    elif(numPassed>0):
        print("10%")
