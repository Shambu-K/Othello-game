# Othello_Game

<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installing-dependencies">Installing Dependencies</a></li>
      </ul>
    </li>
    <li><a href="#Build">Build</a></li>
    <li>
      <a href="#usage">Usage</a></li>
      <ul>
        <li><a href="#using-gui-version">Using gui version</a></li>
        <li><a href="#using-cli-version">Using cli version</a></li>
      </ul>
    <li><a href="#license">License</a></li>
  </ol>
</details



<!-- ABOUT THE PROJECT -->
## About the project
A project with both single and double player based Othello game

## Getting started
Before playing the game some dependies are needed which are listed below.

### Installing Dependencies
- g++-10
```sh
sudo apt-get update
sudo apt install g++-10
```
- fmt library
```sh
sudo apt update
sudo apt install libfmt-dev
```
- SFML library
```sh
sudo apt update
sudo apt-get install libsfml-dev
```

- tgui library
```sh
sudo apt update
sudo add-apt-repository ppa:texus/tgui
sudo apt-get update
sudo apt-get install libtgui-0.9-dev
```

## Build
```sh
git clone https://github.com/IITH-CS1023/cs1023-sdf-project-team-15.git Othello_Game
cd Othello_Game

#to build the executable for gui version
make all
#to run the executable for gui version
make run

#to build the executable for cli version
make all_cli
#to run the executable for cli version
make run_cli
```
## Usage
How to play the game and some rules

### Using gui version
```sh
- First select the mode of play
- Press the mouse where you want to place your coin
- Press "pass" if you dont want to play your turn ("Remember if both players press pass at the same turn then the game will be over there")
```
### Using cli version
```sh
- Enter the coordinate of the block where you want to place your coin
- The game will end if the board is totally filled
- If you want to exit the game press "Crtl+C"
```

## License
Distributed under the GNU3 License. See [LICENSE](LICENSE) for more information.

[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=402094&assignment_repo_type=GroupAssignmentRepo)

