'''
Created on 12/07/22
@author:   Yash Yagnik
Pledge:    I pledge that I have abided by the Stevens Honor System

CS115 - Hw 12 - Date class
'''
DAYS_IN_MONTH = (0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)

class Date(object):
    '''A user-defined data structure that stores and manipulates dates.'''

    # The constructor is always named __init__.
    def __init__(self, month, day, year):
        '''The constructor for objects of type Date.'''
        self.month = month
        self.day = day
        self.year = year

    # The 'printing' function is always named __str__.
    def __str__(self):
        '''This method returns a string representation for the
           object of type Date that calls it (named self).

             ** Note that this _can_ be called explicitly, but
                it more often is used implicitly via the print
                statement or simply by expressing self's value.'''
        return '%02d/%02d/%04d' % (self.month, self.day, self.year)
    
    def copy(self): 
        '''Returns a new object with the same month, day, year 
           as the calling object (self).''' 
        dnew = Date(self.month, self.day, self.year) 
        return dnew

    def equals(self, d2): 
        '''Decides if self and d2 represent the same calendar date, 
            whether or not they are the in the same place in memory.''' 
        return self.year == d2.year and self.month == d2.month and self.day == d2.day
    
    def __repr__(self):
        '''This method also returns a string representation for the object.'''
        return self.__str__()

    # Here is an example of a 'method' of the Date class.
    def isLeapYear(self):
        '''Returns True if the calling object is in a leap year; False
        otherwise.'''
        if self.year % 400 == 0:
            return True
        if self.year % 100 == 0:
            return False
        if self.year % 4 == 0:
            return True
        return False


    def tomorrow(self):
        '''Gives the date of the next day'''
        days = DAYS_IN_MONTH[self.month]

        if self.month == 2:
            if self.isLeapYear() == True:
                if self.day == 29:
                    self.month += 1
                    self.day = 1
                else:
                    self.day += 1
            else:
                    if self.day == 28:
                        self.month += 1
                        self.day = 1
                    else:
                        self.day += 1
        elif days == 30:
            if self.day == 30:
                self.day = 1
                self.month += 1
            else:
                self.day += 1
        elif days == 31:
            
            if self.month == 12:
                if self.day == 31:
                    self.month = 1
                    self.day = 1
                    self.year += 1
                else:
                    self.day += 1
            elif self.day == 31:
                self.day = 1
                self.month += 1
            else:
                self.day += 1


    def yesterday(self):
            '''Gives the date of the previous day'''
            if self.isLeapYear() == True and self.month == 3:
                days = 29
            elif self.month == 1:
                days = DAYS_IN_MONTH[12]
            else:
                days = DAYS_IN_MONTH[self.month - 1]
            if self.day == 1:
                self.day = days
                if self.month == 1:
                    self.month = 12
                    self.year -= 1
                else:
                    self.month -= 1
            else:
                self.day -= 1
    def addNDays(self, N):
        ''' Gives the date N days after the date given'''
        for x in range(0,N):
            print(self)
            self.tomorrow()
        print(self)     
            
    def subNDays(self, N):
        ''' Gives the date N days before; the date given'''
        for x in range(0,N):
            print(self)
            self.yesterday()
        print(self)   

    def isBefore(self, d2):
        ''' Checks if the  date given is before the 2nd date provided'''
        if self.equals(d2) == True:
            return False
        elif self.year < d2.year:
            return True
        elif self.year == d2.year:
            if self.month < d2.month:
                return True
            elif self.month > d2.month:
                return False
            else:
                if self.day < d2.day:
                    return True
                elif self.day > d2.day:
                    return False
        else:
            return False
        
    def isAfter(self, d2):
        ''' Checks if the date given is after the 2nd date provided'''
        if self.equals(d2) == True:
            return False
        elif self.year > d2.year:
            return True
        elif self.year == d2.year:
            if self.month > d2.month:
                return True
            elif self.month < d2.month:
                return False
            else:
                if self.day > d2.day:
                    return True
                elif self.day < d2.day:
                    return False
        else:
            return False

    def diff(self, d2):
        ''' Checks how many days apart 2 input dates are (Will retrun negative numbers)'''
        newSelf = self.copy()
        newd2 = d2.copy()
        days = 0
        if self.equals(d2):
            return days
        elif self.isAfter(d2):
            while newSelf.equals(newd2) != True:
                days += 1
                newSelf.yesterday()
            return days
        else:
            while newSelf.equals(newd2) != True:
                days -= 1
                newSelf.tomorrow()
            return days
        
    def dow(self):
        ''' Retruns the day of the week that the date lands on'''
        currentDate = Date(12, 4, 2022)
        daysBetween = self.diff(currentDate)
        mod = daysBetween % 7
        if mod == 0:
            return 'Sunday'
        elif mod == 1:
            return 'Monday'
        elif mod == 2:
            return 'Tuesday'
        elif mod == 3:
            return 'Wednesday'
        elif mod == 4:
            return 'Thursday'
        elif mod == 5:
            return 'Friday'
        else:
            return 'Saturday'
        
    
