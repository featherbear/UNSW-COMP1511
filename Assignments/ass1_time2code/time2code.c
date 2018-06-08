/*
 * // Progress Log / Change Log //
 * DD/MM/YYYY | HHMM | Entry
 * -----------|------|-------------
 * 22/03/2018 | 2055 | Started assignment
 *            | 2135 | Finish get_local_time function. Basic unit testing
 * 23/03/2018 | 2041 | Removed Darwin from the the ACST -> ACDT timezone offset, as Darwin remains in ACST time
 *            |      | Removed Melbourne from the AEST -> AEDT timezone offset, as Melbourne remains in AEST time
 * 24/03/2018 | 1448 | Added a few more unit tests
 *            | 1518 | Add extra code documentation
 *            | 1530 | Add curly brackets for the if statements because 'style guide'
 *            | 1603 | Documented function logic and testing strategy
 *            | 2214 | Refactored code to put some part of the logic into a function, as per the assignment spec
 *            |      | Modified the DST town check to use the hash define of TOWN_SYDNEY instead of 10 as per the spec ^
 *            |      | Added TRUE and FALSE hash defines
 * 27/03/2018 | 2014 | Changed town checking mechanism to hardcode the cities to check for, as per changed assignment spec
 *            |      | Also reordered the checking logic to check for cities in New Zealand first (lesser cities).
 * 01/04/2018 | 2339 | UPDATE: AEDT doesn't end at UTC 1st April 0300, but rather at UTC 31st March 1700. Fix tomorrow!
 *            |      |         Why can't we just live in a world of epoch
 * 02/04/2018 | 1503 | Refactored code to make more functions
 *            | 1654 | Fixed daylight saving time checking as per issue 01/04/2018_2339
 *            | 1728 | Fixed unit test values
 *            | 1748 | Updated documentation
 * 06/04/2018 | 0117 | Updated documentation
 * 07/04/2018 | 1928 | Modified isCurrentlyDST function to also consider the minutes of the offset. Oops.
 *            |      | Added unit tests for all cities
 *            | 2112 | Added `#define N_TOWNS 14` - further conforming to assignment spec
 * 09/04/2017 | 1249 | Corrected daylight saving end time for Lord Howe Island
 * -----------|------|-------------
 */

/*
 *
 * Your task for this assignment is to write a program that will work out what the local time is in your town so when phoning home you don't call too early or too late and wake your family.
 *
 * To do this, you will write a function to calculate the local time in a given town (in Australia or New Zealand), given the current time in UTC.
 * You will also be required to write a series of tests for this function.
 *
 * The C features needed for this assignment are deliberately simple: ints, arithmetic, if statements and functions.
 * You are not permitted to use C features such as loops and arrays.
 * These wouldn't be particularly helpful and we want you to focus on analysing the problem,
 * designing a solution and testing your solution.
 *
 * You should allow at least two weeks to get it all working perfectly.
 * Start at once and set some time aside to work on it regularly.
 * You will not solve it well in one long intense session.
 * Instead, plan regular periods.
 * It will take much more time to do it than you expect if it is your first coding assignment.
 * There is a lot to learn about tackling a problem like this.
 *
 * = TL;DR =
 * Write a function that converts a UTC time to a local time.
 * Factor in timezones, daylight saving
 * Ignore the date - we just want the time from 0000 to 2359
 *
 */

#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)



// ADD YOUR #defines (if any) here

// The assignment spec is abit ambiguous, we have to check the towns this way???
#define N_TOWNS 14

// Represent true as 1 and false as 0
#define FALSE 0
#define TRUE 1

// Define the months
#define MONTH_JANUARY 1
#define MONTH_FEBRUARY 2
#define MONTH_MARCH 3
#define MONTH_APRIL 4
#define MONTH_MAY 5
#define MONTH_JUNE 6
#define MONTH_JULY 7
#define MONTH_AUGUST 8
#define MONTH_SEPTEMBER 9
#define MONTH_OCTOBER 10
#define MONTH_NOVEMBER 11
#define MONTH_DECEMBER 12

int get_local_time(int town, int utc_month, int utc_day, int utc_time);

void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int isValidInputs(int town, int utc_month, int utc_day, int utc_time);

int isValidMonthDay(int utc_month, int utc_day);

int getOffset(int town);

int getDSTOffset(int town);

int isCurrentlyDST(int town, int utc_month, int utc_day, int utc_time);

int applyOffset(int basetime, int offset);

// DO NOT CHANGE THIS FUNCTION

// This main function won't be marked as part of the assignment
// It tests the functions you have to write.
// Do not change this main function.  If it does not work with
// your functions you have misunderstood the assignment.
int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}


int isValidInputs(int town, int utc_month, int utc_day, int utc_time) {
    /* Validate the inputs of the function */
    if (town < 0 || town >= N_TOWNS) return FALSE; // The value of `town` must be 0..N_TOWNS

    // Not defining months here, because these are hard-coded and will-never-change-ever values
    if (utc_month < 1 || utc_month > 12) return FALSE; // The value of `utc_month` must be 1..12
    if (utc_day < 1 || utc_day > 31) return FALSE; // The value of `utc_day` must be 1..31

    if (utc_time < 0) { return FALSE; } // utc_time must be greater than or equal to zero
    if (utc_time / 100 > 23) { return FALSE; } // Strip of the last two digits to get the hours, must be 0..23
    if (utc_time % 100 > 59) { return FALSE; } // Extract the last two digits to get minutes, must be 0..59
    // Not checking if `utc_time > 2359` since it's redundant

    return TRUE;
};

int isValidMonthDay(int utc_month, int utc_day) {
    /* Validate that the day `utc_day` is possible in month `utc_month` */
    //
    //     ♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪
    //    ♪ 30 days has September, April, June and November.  ♪
    //   ♪ All the rest have 31 except for February alone.  ♪
    //  ♪ Which has 28 days clear, and 29 each leap year! ♪
    // ♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪♪

    // Check that 30-day months are not matched with day 31; Ignoring February as it is covered in the next check
    if (utc_day == 31 && (utc_month == MONTH_SEPTEMBER
                          || utc_month == MONTH_APRIL
                          || utc_month == MONTH_JUNE
                          || utc_month == MONTH_NOVEMBER)) { return FALSE; }

    // In 2018, February only has 28 days!
    if (utc_month == MONTH_FEBRUARY && utc_day > 28) { return FALSE; }
    return TRUE;
}

int getOffset(int town) {
    // Return the standard timezone offset for the town `town`
    int offset = 0;
    if (town == TOWN_BRISBANE
        || town == TOWN_CANBERRA
        || town == TOWN_HOBART
        || town == TOWN_MELBOURNE
        || town == TOWN_SYDNEY) { offset = TIMEZONE_AEST_OFFSET; }
    else if (town == TOWN_ADELAIDE
             || town == TOWN_BROKEN_HILL
             || town == TOWN_DARWIN) { offset = TIMEZONE_ACST_OFFSET; }
    else if (town == TOWN_PERTH) { offset = TIMEZONE_AWST_OFFSET; }
    else if (town == TOWN_EUCLA) { offset = TIMEZONE_ACWST_OFFSET; }
    else if (town == TOWN_LORD_HOWE_IS) { offset = TIMEZONE_LHST_OFFSET; }
    else if (town == TOWN_AUCKLAND
             || town == TOWN_CHRISTCHURCH
             || town == TOWN_WELLINGTON) { offset = TIMEZONE_NZST_OFFSET; }

    assert(offset != 0); // All 14 city cases should be covered
    return offset;
}

int getDSTOffset(int town) {
    // Return the daylight saving timezone offset for the town `town`
    // Returns 0 if there is no associated DST offset

    int offset = 0;

    // Adjust the timezone offset to AEDT if the city is either Canberra, Hobart, Melbourne or Sydney
    // Note: Brisbane doesn't have AEDT, but rather remains in AEST throughout the year
    if (town == TOWN_CANBERRA
        || town == TOWN_HOBART
        || town == TOWN_MELBOURNE
        || town == TOWN_SYDNEY) { offset = TIMEZONE_AEDT_OFFSET; }

    // Adjust the timezone offset to ACDT if the city is either Adelaide or Broken Hill
    // Note: Darwin doesn't have ACDT, but rather remains in ACST throughout the year
    if (town == TOWN_ADELAIDE || town == TOWN_BROKEN_HILL) { offset = TIMEZONE_ACDT_OFFSET; }

    // Adjust the timezone offset to LHDT if the city is Lord Howe Island
    if (town == TOWN_LORD_HOWE_IS) { offset = TIMEZONE_LHDT_OFFSET; }

    // Adjust the timezone offset to NZDT if the city is Auckland, Christchurch or Wellington
    if (town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH ||
        town == TOWN_WELLINGTON) { offset = TIMEZONE_NZDT_OFFSET; }

    return offset;
}

int isCurrentlyDST(int town, int utc_month, int utc_day, int utc_time) {
    // Check if the current date and time with a specific city is associated to a daylight saving time zone
    // As per the assignemnt spec - we're hard-coding the daylight saving dates to 2018

    int tz_offset = getOffset(town); // Get the offset of the standard timezone
    int tz_dst_offset = getDSTOffset(town); // Get the offset of the daylight saving timezone

    // Get the the DST boundary times of the town relative to UTC
    int dstEndBoundary_relativeToUTC = applyOffset(300, -tz_dst_offset);
    int dstStartBoundary_relativeToUTC = applyOffset(200, -tz_offset);

    // Lord Howe Island's daylight saving end time is different to the usual 3am time
    if (town == TOWN_LORD_HOWE_IS) dstEndBoundary_relativeToUTC = applyOffset(200, -tz_offset);

    // As the assignment only wants us to factor in New Zealand and Australia, we can
    // define the boundary times just once, as both countries have the same boundary times

    // Check which town we are inspecting, as the dates differ
    if (town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH || town == TOWN_WELLINGTON) {
        // We're in New Zealand

        // Daylight Saving is from 30th September 2am to 1st April 2018 3am
        if (utc_month < MONTH_MARCH
            || (utc_month == MONTH_MARCH && utc_day < 31)
            || (utc_month == MONTH_MARCH && utc_day == 31 && utc_time < dstEndBoundary_relativeToUTC)) {
            return TRUE;
        }
        if (utc_month > MONTH_SEPTEMBER
            || (utc_month == MONTH_SEPTEMBER && utc_day == 29 && utc_time >= dstStartBoundary_relativeToUTC)
            || (utc_month == MONTH_SEPTEMBER && utc_day == 30)) {
            return TRUE;
        }
    } else {
        // We're in Australia

        // Daylight Saving is from 7th October 2018 2am to 1st April 2018 3am
        if (utc_month < MONTH_MARCH
            || (utc_month == MONTH_MARCH && utc_day < 31)
            || (utc_month == MONTH_MARCH && utc_day == 31 && utc_time < dstEndBoundary_relativeToUTC)) {
            return TRUE;
        }
        if (utc_month > MONTH_OCTOBER
            || (utc_month == MONTH_OCTOBER && utc_day == 6 && utc_time >= dstStartBoundary_relativeToUTC)
            || (utc_month == MONTH_OCTOBER && utc_day >= 7)) {
            return TRUE;
        }
    }
    return FALSE;
}

int applyOffset(int basetime, int offset) {
    // exploit the fact that stored integers strip off the decimal
    // 2359 => 23; 115 => 1
    int hours = basetime / 100;

    // Grab the last two digits from `utc_time` by finding the remainded when divided by 100
    // 2359 => 59; 115 => 15
    int minutes = basetime % 100;

    // ----------------------------------------------- //

    // Split offset into hours and minutes, to makes the addition of time easier.
    int offsetHours = offset / 100; // exploit the fact that stored integers strip off the decimal
    int offsetMinutes = offset % 100; // get the last two digits (aka the minutes) of the offset

    // Add the minutes first, because if the minutes exceed 59, then that means that a new hour has passed
    minutes += offsetMinutes;

    if (minutes > 59) {
        hours += 1; // Increment an hour
        minutes %= 60;
    } else if (minutes < 0) {
        minutes = (minutes + 60) % 60;
        hours -= 1;
    }

    // Now we can add the offset hours
    hours += offsetHours;

    // Finally, return the integer that represents the time
    // hours % 24 => this restricts the range of the hour integer to the range of 0..23
    // If the hour was 24, then 24 % 24 == 0 (which is midnight the next day)
    // If the hour was 25, then 25 % 24 == 1 (which is 1am of the next day)
    return ((hours + 24) % 24) * 100 + minutes;
}





// Given an AUS/NZ town and a 2018 UTC time, return the local time in the AUS/NZ town.
// The time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs

// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes

// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero


int get_local_time(int town, int utc_month, int utc_day, int utc_time) {
    /* ================================================================================================================
    *  FUNCTION LOGIC :)
    *  1) Ensure that the inputs (town, utc_month, utc_day, utc_time) are valid.
    *  2) Check for criteria specific to the month (ie some months cannot have 31 days, february has 28 days in 2018)
    *  3) Check if the current time falls within the daylight saving period of a said city
    *  4) Adjust the time zone offset of the city.
    *  5) Add the time zone offset to the UTC time
    *  ============================================================================================================== */

    // 1) Ensure that the inputs (town, utc_month, utc_day, utc_time) are valid.
    if (!isValidInputs(town, utc_month, utc_day, utc_time)) return INVALID_INPUT;

    // 2) Check for criteria specific to the month (ie some months cannot have 31 days, february has 28 days in 2018)
    if (!isValidMonthDay(utc_month, utc_day)) return INVALID_INPUT;

    int offset = 0; // Initialise the offset variable

    // 3) Check if the current time falls within the daylight saving period of a said city
    // 4) Adjust the time zone offset of the city.
    if (isCurrentlyDST(town, utc_month, utc_day, utc_time)) {
        offset = getDSTOffset(town);
    }

    // Some towns however, do not follow DST, so we need account for these missing DST timezones
    if (offset == 0) {
        offset = getOffset(town);
    }

    // 5) Add the time zone offset to the UTC time
    return applyOffset(utc_time, offset);
}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY
/* =====================================================================================================================
** TESTING STRATEGY
**
** NOTE: Not using the defines for the months as the assignment spec says to 'implement them in exactly the same way'
**
**
** > Testing for basic invalid inputs
** - Ensure that `town` is in the range of 0..13
** - Ensure that `utc_month` is in the range of 1..12
** - Ensure that `utc_day` is in the range of 1..31
** - Ensure that `utc_time` is in the range of 0..2359
** - Ensure that the last two digits of `utc_time` is in the range of 0..59
**
** > Testing for special cases of invalid inputs
** - Check that an error occurs when pairing a month with an invalid day in that month
** \-- February 29th 2018 doesn't exist as 2018 is not a leap year
** \-- February 30th 2018 doesn't exist (ever)
** \-- February 31st 2018 doesn't exist (ever)
** \-- April 31st 2018 doesn't exist (ever)
** \-- June 31st 2018 doesn't exist (ever)
** \-- September 31st 2018 doesn't exist (ever)
** \-- November 31st 2018 doesn't exist (ever)
**
**
** > Testing for program logic correctness
** - Check for all time zone boundaries (ie 1:59am, 2:00am, 2:01am ... 2:59am, 3:00am, 3:01am) relative to UTC
** =====================================================================================================================
*/

// run unit tests for get_local_time
void run_unit_tests(void) {
    // 2 example unit tests
    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // ADD YOUR ASSERT STATEMENTS HERE

    // Copy and paste the autotest, ensure that the basic cases work for all (most) of the cities/towns
    assert(get_local_time(TOWN_CHRISTCHURCH, 5, 15, 859) == 2059);
    assert(get_local_time(TOWN_SYDNEY, 4, 5, 0) == 1000);
    assert(get_local_time(TOWN_ADELAIDE, 6, 30, 1030) == 2000);
    assert(get_local_time(TOWN_BRISBANE, 8, 17, 2015) == 615);
    assert(get_local_time(TOWN_AUCKLAND, 4, 27, 800) == 2000);
    assert(get_local_time(TOWN_PERTH, 1, 30, 2311) == 711);
    assert(get_local_time(TOWN_PERTH, 5, 2, 2000) == 400);
    assert(get_local_time(TOWN_CHRISTCHURCH, 10, 6, 2230) == 1130);
    assert(get_local_time(TOWN_CANBERRA, 12, 16, 1428) == 128);
    assert(get_local_time(TOWN_DARWIN, 11, 1, 339) == 1309);
    assert(get_local_time(TOWN_HOBART, 7, 8, 1300) == 2300);
    assert(get_local_time(TOWN_MELBOURNE, 9, 27, 1354) == 2354);
    assert(get_local_time(TOWN_WELLINGTON, 1, 5, 924) == 2224);
    assert(get_local_time(TOWN_BRISBANE, 4, 18, 1400) == 0);
    assert(get_local_time(TOWN_BRISBANE, 10, 8, 1106) == 2106);
    assert(get_local_time(TOWN_SYDNEY, 10, 29, 1201) == 2301);
    assert(get_local_time(TOWN_DARWIN, 2, 17, 2345) == 915);
    assert(get_local_time(TOWN_AUCKLAND, 8, 7, 2200) == 1000);
    assert(get_local_time(TOWN_EUCLA, 9, 5, 1015) == 1900);
    assert(get_local_time(TOWN_BROKEN_HILL, 1, 1, 1000) == 2030);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 1, 2215) == 845);
    assert(get_local_time(TOWN_EUCLA, 2, 6, 2359) == 844);
    assert(get_local_time(TOWN_BROKEN_HILL, 7, 17, 117) == 1047);


    // Testing the range of the `town` variable
    assert(get_local_time(-1, 1, 1, 0) == INVALID_INPUT);
    assert(get_local_time(14, 1, 1, 0) == INVALID_INPUT);


    // Testing the range of the `utc_month` variable
    assert(get_local_time(-1, 0, 1, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 0, 1, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 13, 1, 0) == INVALID_INPUT);


    // Testing the range of the `utc_day` variable
    assert(get_local_time(TOWN_SYDNEY, 1, -1, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 1, 0, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 1, 30, 0) == 1100);
    assert(get_local_time(TOWN_SYDNEY, 1, 31, 0) == 1100);
    assert(get_local_time(TOWN_SYDNEY, 1, 32, 0) == INVALID_INPUT);


    // February has 28 days in 2018
    assert(get_local_time(TOWN_SYDNEY, 2, 28, 0) == 1100);
    assert(get_local_time(TOWN_SYDNEY, 2, 29, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 2, 30, 0) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 2, 31, 0) == INVALID_INPUT);


    // April has 30 days
    assert(get_local_time(TOWN_SYDNEY, 4, 29, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 4, 30, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 4, 31, 0) == INVALID_INPUT);


    // June has 30 days
    assert(get_local_time(TOWN_SYDNEY, 6, 29, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 6, 30, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 6, 31, 0) == INVALID_INPUT);


    // September has 30 days
    assert(get_local_time(TOWN_SYDNEY, 9, 29, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 9, 30, 0) == 1000);
    assert(get_local_time(TOWN_SYDNEY, 9, 31, 0) == INVALID_INPUT);


    // November has 30 days
    assert(get_local_time(TOWN_SYDNEY, 11, 29, 0) == 1100);
    assert(get_local_time(TOWN_SYDNEY, 11, 30, 0) == 1100);
    assert(get_local_time(TOWN_SYDNEY, 11, 31, 0) == INVALID_INPUT);


    // Check for invalid times
    assert(get_local_time(TOWN_SYDNEY, 3, 22, -1000) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 3, 22, 2360) == INVALID_INPUT);
    assert(get_local_time(TOWN_SYDNEY, 3, 22, 2400) == INVALID_INPUT);


    // Ensure that our daylight saving start limits are working
    // 7th October 2am AEST is 6th October 4pm UTC
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1400) == 0); // 2PM + 10 (AEST) = 12AM
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1500) == 100);
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1559) == 159);
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1600) == 300); // Instead of becoming 2AM, offset becomes AEDT (+11)
    assert(get_local_time(TOWN_SYDNEY, 10, 6, 1601) == 301);

    // Ensure that our daylight saving end limits are working
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1300) == 0); // 1PM + 11 (AEDT) = 12AM
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1400) == 100);
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1500) == 200);
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1559) == 259);
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1600) == 200); // Instead of becoming 3AM, offset becomes AEST (+10)
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1601) == 201);


    // Ensure that our daylight saving start limits are working
    // 30th September 2am NZST is 29th September 2pm UTC
    assert(get_local_time(TOWN_AUCKLAND, 9, 29, 1200) == 0); // 12PM + 12 (NZST) = 12AM
    assert(get_local_time(TOWN_AUCKLAND, 9, 29, 1300) == 100);
    assert(get_local_time(TOWN_AUCKLAND, 9, 29, 1359) == 159);
    assert(get_local_time(TOWN_AUCKLAND, 9, 29, 1400) == 300); // Instead of becoming 2AM, offset becomes NZDT (+13)
    assert(get_local_time(TOWN_AUCKLAND, 9, 29, 1401) == 301);

    // Ensure that our daylight saving end limits are working
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1100) == 0); // 11AM + 13 (NZDT) = 12AM
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1200) == 100);
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1300) == 200);
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1359) == 259);
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1400) == 200); // Instead of becoming 3AM, offset becomes AEST (+10)
    assert(get_local_time(TOWN_AUCKLAND, 3, 31, 1401) == 201);




    // Other towns


    // Adelaide and Broken Hill move between ACST and AEDT
    assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1629) == 259);
    assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1630) == 200);
    assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1631) == 201);

    assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1629) == 259);
    assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1630) == 200);
    assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1631) == 201);


    // Canberra, Hobart, Melbourne (and Sydney) move between AEST and AEDT
    assert(get_local_time(TOWN_CANBERRA, 3, 31, 1559) == 259);
    assert(get_local_time(TOWN_CANBERRA, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_CANBERRA, 3, 31, 1601) == 201);
    assert(get_local_time(TOWN_HOBART, 3, 31, 1559) == 259);
    assert(get_local_time(TOWN_HOBART, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_HOBART, 3, 31, 1601) == 201);
    assert(get_local_time(TOWN_MELBOURNE, 3, 31, 1559) == 259);
    assert(get_local_time(TOWN_MELBOURNE, 3, 31, 1600) == 200);
    assert(get_local_time(TOWN_MELBOURNE, 3, 31, 1601) == 201);

    assert(get_local_time(TOWN_CANBERRA, 10, 6, 1559) == 159);
    assert(get_local_time(TOWN_CANBERRA, 10, 6, 1600) == 300);
    assert(get_local_time(TOWN_CANBERRA, 10, 6, 1601) == 301);
    assert(get_local_time(TOWN_HOBART, 10, 6, 1559) == 159);
    assert(get_local_time(TOWN_HOBART, 10, 6, 1600) == 300);
    assert(get_local_time(TOWN_HOBART, 10, 6, 1601) == 301);
    assert(get_local_time(TOWN_MELBOURNE, 10, 6, 1559) == 159);
    assert(get_local_time(TOWN_MELBOURNE, 10, 6, 1600) == 300);
    assert(get_local_time(TOWN_MELBOURNE, 10, 6, 1601) == 301);


    // Brisbane stays in AEST throughout the year
    assert(get_local_time(TOWN_BRISBANE, 1, 1, 0) == 1000);
    assert(get_local_time(TOWN_BRISBANE, 4, 1, 300) == 1300);
    assert(get_local_time(TOWN_BRISBANE, 4, 1, 300) == 1300);
    assert(get_local_time(TOWN_BRISBANE, 12, 31, 2359) == 959);


    // Darwin stays in ACST throughout the year
    assert(get_local_time(TOWN_DARWIN, 1, 1, 0) == 930);
    assert(get_local_time(TOWN_DARWIN, 4, 1, 300) == 1230);
    assert(get_local_time(TOWN_DARWIN, 4, 1, 300) == 1230);
    assert(get_local_time(TOWN_DARWIN, 12, 31, 2359) == 929);


    // Eucla stays in ACWST throughout the year
    assert(get_local_time(TOWN_EUCLA, 1, 1, 0) == 845);
    assert(get_local_time(TOWN_EUCLA, 4, 1, 300) == 1145);
    assert(get_local_time(TOWN_EUCLA, 4, 1, 300) == 1145);
    assert(get_local_time(TOWN_EUCLA, 12, 31, 2359) == 844);


    // Lord Howe Island moves between LHST and LHDT
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1529) == 229);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1530) == 200);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1531) == 201);

    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1529) == 159);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1530) == 230);
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1531) == 231);


    // Perth stays in AWST throughout the year
    assert(get_local_time(TOWN_PERTH, 1, 1, 0) == 800);
    assert(get_local_time(TOWN_PERTH, 4, 1, 300) == 1100);
    assert(get_local_time(TOWN_PERTH, 4, 1, 300) == 1100);
    assert(get_local_time(TOWN_PERTH, 12, 31, 2359) == 759);


    // Christchurch, Wellington (and Auckland) move between NZST and NZDT
    assert(get_local_time(TOWN_CHRISTCHURCH, 9, 29, 1359) == 159);
    assert(get_local_time(TOWN_CHRISTCHURCH, 9, 29, 1400) == 300);
    assert(get_local_time(TOWN_CHRISTCHURCH, 9, 29, 1401) == 301);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1359) == 159);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1400) == 300);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1401) == 301);

    assert(get_local_time(TOWN_CHRISTCHURCH, 3, 31, 1359) == 259);
    assert(get_local_time(TOWN_CHRISTCHURCH, 3, 31, 1400) == 200);
    assert(get_local_time(TOWN_CHRISTCHURCH, 3, 31, 1401) == 201);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1359) == 159);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1400) == 300);
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1401) == 301);


    // Random assert statements to reach the requirement of minimum 40 asserts
    // Andrew Bennet said to put birthdays in!!!111oneoneone
    assert(get_local_time(TOWN_SYDNEY, 9, 22, 930) == 1930); // I was born 7:30pm (ish) on the 22nd September!?!?!?!?
    assert(get_local_time(TOWN_SYDNEY, 3, 24, 0) == 1100); // Brother was born on the 24th March
    assert(get_local_time(TOWN_SYDNEY, 5, 16, 830) == 1830); // Dad was born on the 16th May!
    assert(get_local_time(TOWN_SYDNEY, 11, 15, 0) == 1100); // Mum was born on the 15th November!

    // ...
    assert(get_local_time(TOWN_SYDNEY, 12, 25, 9999) == INVALID_INPUT); // Girlfriend's birthda-oh wait. I'm an engineer
}