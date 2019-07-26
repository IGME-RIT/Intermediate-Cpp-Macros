/*
Macros
(c) 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



// Include iostream for output during the program.
#include <iostream>
using namespace std;

// Macros are a powerful and dangerous tool in C and C++.
// They are helpful, because they allow you to avoid rewriting code.
// They are dangerous, because they can cause all kinds of unexpected bugs.


// Start of main function
int main() 
{
    // The best and most accurate way to think about macros, is that they copy paste code.
    {
        // An example macro might look like this:
        #define Average(a, b) (a + b) / 2

        // Taking this apart we have
        // #define          - Tells us that we are defining something for the compiler to use.
        // Average(a, b)    - The identifier, and the "parameters."
        // (a + b) / 2      - The body of the macro.

        // We can now use the macro like so:
        // This inputs our values "4" and "7", into the macro, and then does it.
        cout << "Average(4, 7): " << Average(4, 7) << endl;

        // When the compiler is done preprocessing, the code will look something like this:
        cout << "(4 + 7) / 2: " << (4 + 7) / 2 << endl;

        // Which is particularly convenient, because we can put in floating point types, and it will print out a float!
        cout << "Average(4.f, 7.f): " << Average(4.f, 7.f) << endl;


        // The question then becomes, why not just create a function?
        // The answer: A macro produces slightly less overhead for the program.
        // When calling a function, the computer needs to move to a different part of the program code.
        // After executing the function, it will then need to return to where it was.

        // If your function is really small (like adding two numbers and dividing by 2)
        // It ends up being much more efficient to just rewrite the code every time.
        // Of course, programmers are lazy, and don't want to rewrite the same code over and over.
        // Imagine if you ended up needing to change the way that code worked.
        // You'd have to go to all of the locations that it changed, and change it!
    }
    cin.get();


    {
        // So now you have an idea of how powerful macros can be.
        // Let's look at all the ways you can use macros to add bugs to your program.

        #define Total(a, b, c) a + b + c    // Looks simple enough right?


        cout << "int x = 3 * Total(1, 2, 3);" << endl;
        int x = 3 * Total(1, 2, 3);         // You might expect x to be 3 * (1 + 2 + 3) = 18
                                            // You would be wrong.
        cout << "x: " << x << endl;         // x is actually 3 * 1 + 2 + 3 = 8
                                            // Our macro doesn't use parenthesis.

        // There are two ways to fix this:
        // A) Add parens outside of the Macro:
        cout << "3 * (Total(1, 2, 3)): " << 3 * (Total(1, 2, 3)) << endl;   // If I catch you doing this
                                                                            // I will reach through the computer and slap you!

        // B) Add parens inside your Macro:
        #define CorrectTotal(a, b, c) (a + b + c)                           // DO THIS THE FIRST TIME!
        cout << "3 * CorrectTotal(1, 2, 3): " << 3 * CorrectTotal(1, 2, 3) << endl;


        // A Similar mistake can arise in this situation:
        #define Area(a, b) (a * b)

        cout << "int area = Area(1 + 2, 1 + 2);" << endl;
        int area = Area(1 + 2, 1 + 2);      // You would expect to get 9 here.
        cout << "area: " << area << endl;   // Nope, 5.


        // Again, parenthesis are very important
        #define CorrectArea(a, b) ((a) * (b))

        // At this point, you may be starting to see some of the drawbacks of macros.
    }
    cin.get();




    {
        // Those didn't seem so bad right?
        // That's ok, if that didn't scare you. Here's some other stupid things you can do with macros:

        #define if(a) if(!a) // That's right, I just defined if to be inverted.

        if (true == false)
        {
            cout << "true == false" << endl;
        }

        // While we're at it, lets change some other things:
        #define while(a) while(a-->0)
        #define bool float
        #define wub <<"\nwub\n"<<
        #define true i

        bool i = 3.14159;     // true is i, which is a bool that is actually a float that is 3.14159

        while (true)
        {
            if(true == 0)
                cout wub "hi there!" wub true wub endl;    // This is C++ right?
        }

        // I'm starting to get confused, so I'm going to undo that.
        #undef if
        #undef while
        #undef bool
        #undef true
        #undef wub

    }
    cin.get();


    {
        // Now that we know how evil macros can be, let's look at some other stupid uses for macros


        // Here, I define a different way to write a for loop that loops n times:
        #define Loop(n) for(int i = 0; i < n; i++)  // Seems simple enough.


        Loop(3) { // Now I can loop without writing the whole thing! Cool!
            cout << "repeat this" << endl;
        }

        // Why is this bad?
        // Loop secretly declares an i variable, and we can change it while inside the loop without knowing what loop does:

        /*
        int i = 3;
        Loop(3) {
            i--;
            cout << i << endl;
        }
        */

        // Reading this code, I would expect it to loop 3 times, and decrement i to 0.
        // In reality, it never ends, because the i being decremented refers to the i used in the macro!


    }
    cin.get();


    {
        // Multi line macros:

        // All of the macros so far have been single lines.
        // This is because of how #define works. (it takes whatever's left on that line.)
        // We can get around this with \, which makes the compiler keep reading on the next line as if there was no newline.
        // We use braces {} to change scope, so that the variable c doesn't exist after the macro is finished.
        // (Without them, calling DoStuff twice would declare c twice)
        #define DoStuff(a, b)\
        {\
            int c = a + b;\
            cout << c << endl;\
        }
        // This could have been written in one line, but that's not the point.
        // Doing this makes your code more readable.

        
        DoStuff(3, 4);  // Test it out!

        // Unfortunately, this presents even more problems:
        // It doesn't really need a semicolon, because it already has on in it's code:
        // DoStuff(3, 4)

        // This won't compile:
        
        /*
        if (true)
            DoStuff(1, 2);
        else
            cout << "something else" << endl;
        */
        
        // It becomes this:
        /*
        if (true) 
        {
            int c = 3 + 4;
            cout << c << endl;
        }; // <------------------ This semi colon right here, is from the semicolon after DoStuff(3, 4);
        else                                                    // It screws up our if else
            cout << "something else" << endl;
        */

        // This can be avoided by just not including the semicolon, but it will look weird:
        if (true)
            DoStuff(1, 1)
        else
            DoStuff(2, 2);


        // The alternative strategy for doing it looks like this:
        // With a do while loop, we have the same encapsulation that braces give us, but a do while also requires a semicolon at the end.
        #define DoOtherStuff(a, b)\
        do{\
        int c = (a)+(b);\
        cout << c << endl;\
        } while (0)

        // DoOtherStuff(1, 1)   // No semi colon -> compiler complains.

        // In an if statement
        if (true)
            DoOtherStuff(3, 3);
        else
            DoOtherStuff(4, 4);
    
    }
    cin.get();


    return 0;
}