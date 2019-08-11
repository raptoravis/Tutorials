// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <vector>
#include <memory>

// Welcome to "Dive into C++11", part 5.
// http://vittorioromeo.info

// In this tutorial we're gonna cover a common game-development
// topic: entity management.

// I highly recommend watching part 1 and part 4
// before watching this video.

// Let's dive in!

// Let's say we're making an arkanoid/breakout clone.
// There are various game elements that the player interacts with:
// * Ball
// * Bricks
// * Powerups
// * Paddle
// * ...

// A possible way of dealing with all these elements is creating
// a class for every element, with an `update` method and a `draw`
// method, then use `std::vectors` of `std::unique_ptr` to manage
// their lifetime. Here's an example:

namespace VeryNaiveArkanoid
{
    // Here are the game element classes:

    struct Ball
    {
        void update(float mFT) { /* ... */}
        void draw() { /* ... */}
    };

    struct Brick
    {
        void update(float mFT) { /* ... */}
        void draw() { /* ... */}
    };

    struct Paddle
    {
        void update(float mFT) { /* ... */}
        void draw() { /* ... */}
    };

    struct Powerup
    {
        void update(float mFT) { /* ... */}
        void draw() { /* ... */}
    };

    // And there is the "game" class itself:

    struct Game
    {
        std::vector<std::unique_ptr<Ball>> balls;
        std::vector<std::unique_ptr<Brick>> bricks;
        std::vector<std::unique_ptr<Paddle>> paddles;
        std::vector<std::unique_ptr<Powerup>> powerups;

        // Note that we could also decide against using smart
        // pointers, and simply store game elements contiguously
        // in the vectors. This would improve performance, but
        // would make keeping track of specific instances of
        // these game elements very hard, as pointers to them
        // would get invalidated when the vectors are internally
        // resized.

        void update(float mFT)
        {
            for(auto& b : balls) b->update(mFT);
            for(auto& b : bricks) b->update(mFT);
            for(auto& p : paddles) p->update(mFT);
            for(auto& p : powerups) p->update(mFT);
        }

        void draw()
        {
            for(auto& b : balls) b->draw();
            for(auto& b : bricks) b->draw();
            for(auto& p : paddles) p->draw();
            for(auto& p : powerups) p->draw();
        }
    };

    // As you can probably see, this approach is very difficult
    // to maintain and expand. For `N` game element types, you need
    // `N` containers, and `N` function calls.

    // Adding another game element would require the developer
    // to modify the game class itself.

    // This approach is confusing, error-prone and not scalable.

    // Something similar to this code segment is only appropriate
    // for small games with a small number of game element types.
}

int main() {}
// Let's move on, and check out a (possibly) better implementation.