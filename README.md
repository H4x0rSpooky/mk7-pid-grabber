# MK7 PID Grabber
This is a Principal ID grabber CTRPluginFramework designed for Mario Kart 7 on the Nintendo 3DS.

It's purpose is to allow people to report cheaters in their in-game lobbies or opponent list on platforms like [Pretendo](https://pretendo.network/).

> [!TIP]
> The Principal ID is the identifier of any user on the Nintendo 3DS. It's basically the friend code of the system but packed into a different series of numbers. It helps people be unique and to identify them.

> [!NOTE]
> Principal IDs can still be spoofed, I might include a method to get the clean Principal ID instead in the future.

# How to use the plugin
Head over to the [releases](https://github.com/H4x0rSpooky/mk7-pid-grabber/releases/latest) and grab the latest `mk7-pid-grabber.3gx` file.

Create a folder on your system's sd card: `sd:luma/plugins/<Title ID>/`.

Use the the following `Title ID` depending on your version:
- **USA**: `0004000000030800`
- **EUR**: `0004000000030700`
- **JPN**: `0004000000030600`

> [!NOTE]
> There are more versions however those are the most common ones. If yours isn't included in this, find it through `FBI` under installed titles or [3dsdb](https://3dsdb.com/).

Once that's done, simply place the `mk7-pid-grabber.3gx` file into the folder you just created.

While you're in thr HOME-menu, open the `Rosalina Menu`. The key combination to enter it is `L + DPad Down + Select`. Navigate to the `Plugin Loader`, press `A` on it once to change it to `Enabled` and go to `Save Settings`. After that, simply close the menu again and launch your game. It should flash blue once, which indicates that the plugin has successfully been loaded. If that doesn't occur, you did something wrong and should go through these steps again.

The default menu activator for `CTRPF` is `Select`, this is the creators' choice.

# How to build the project
> [!NOTE]
> This is for windows users

Make sure you have the latest version of:
- [git](https://git-scm.com/downloads)
- [devkitPro](https://devkitpro.org/wiki/Getting_Started)
- [Python](https://www.python.org/downloads/)

After that, download the source code and follow the steps to install [CTRPluginFramework](https://gitlab.com/thepixellizeross/ctrpluginframework). Don't forget to also run `pacman -S 3gxtool` in order to install [3gxtool](https://gitlab.com/thepixellizeross/3gxtool) which is required to compile `3gx` files.

Once all the steps are completed, run the `build.bat` file inside the source and let it compile the file.

# Reporting bugs or issues
Just direct message me on Discord.

**My username:** `h4x0rspooky`
> [!CAUTION]
> Any other person isn't me

# Credits
- H4x0rSpooky for creating this project
- [Anto726](https://github.com/Anto726) for the things he taught me
- [Nanquitas](https://github.com/Nanquitas) for creating CTRPluginFramework
- [PabloMK7](https://github.com/PabloMK7) for maintaining CTRPluginFramework
