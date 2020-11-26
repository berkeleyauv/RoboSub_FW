# URAB_MATE_FW
MATE Firmware for Underwater Robotics at Berkeley (UR@B)

## How to Use

	git clone --recursive https://github.com/dragonlock2/URAB_MATE_FW.git

Install [Mbed Studio](https://os.mbed.com/studio/). Switch workspaces to this repo. Select the correct "Active Program" and "Target" to match your needs.

## How to Add a New Project

	cd URAB_MATE_FW/
	cp -a Template/ <Project Name> # also copies symlinks

Select a target and click "Build" to check that everything worked.

## How to Add External Libraries

If you find a library online that you want to use, don't use Mbed Studio's builtin method! Instead add it as a submodule to our repo and symlink it.

	git submodule add <link to library's git>
	cd <Project Folder>
	ln -s ../libs/<Library Folder> <Library Folder>

You can also optionally git checkout the branch/commit you want (from within the library's folder).

## How to Make a New Library

If you're adding support for something new, first check the libs/ folder to see if we already added it. If it exists, use a relative symlink to add it to your project.

	cd <Project Folder>
	ln -s ../libs/<Library Folder> <Library Folder>

If it's not there, it's time to make your own! Add it to the libs/ folder (as a new folder) so others can use it. Symlink it like above. Put all of your .h and .cpp files for your library in this new folder.

## Updating External Libraries

If a new version of Mbed or one of the libraries we use comes out, you can update it as follows:

