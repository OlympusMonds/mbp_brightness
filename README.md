# Screen brightness changer for MacBookPro running Ubuntu

I'm running Ubuntu 16.04 on my 2012 MBP, and I recently switched to using the Awesome Window Manager.
A bunch of the bells and whistles that come with Unity no longer worked, in particular changing the 
backlight brightness.

Some quick investigation didn't show where Unity was doing this, but I did find the actual mechanism. 
I wrote this code to create a binary to interact with it, with the uid set to root.

# How to use

## Compile

    git clone https://github.com/OlympusMonds/mbp_brightness.git
    cd mbp_brightness
    make
    cp backlight ~/bin/  # make sure ~/bin is in your $PATH

## Set user as root

    sudo chown root ~/bin/backlight
    sudo chmod u+s ~/bin/backlight

## Try it out

    backlight --inc 10  # increase by 10% of total brightness
    backlight --dec 10  # decrease by 10% of total brightness
    backlight --get     # get current percentage of total brightness

## Add it to your Awesome WM config

In .config/awesome/rc.lua, just before the "-- Standard program" section, I added:

    -- Brightness
    awful.key({}, "XF86MonBrightnessDown", function() awful.util.spawn("backlight --dec 5") end),
    awful.key({}, "XF86MonBrightnessUp", function() awful.util.spawn("backlight --inc 5") end),

Restart awesome to see if it works.
