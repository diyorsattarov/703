# cpp-apm

cpp-apm is a simple and lightweight tool designed to measure and track user activity through mouse and keyboard clicks. By recording the number of clicks, it calculates the Actions Per Minute (APM) to provide insights into user engagement and productivity over time. This utility is especially useful for analyzing and optimizing user interaction with software applications and games on Windows systems.

## Table of Contents

- [cpp-apm](#project-name)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
  - [Usage](#usage)
  - [Features](#features)
  - [Contributing](#contributing)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

## Introduction

cpp-apm is a versatile and valuable tool that measures user engagement and productivity through tracking mouse and keyboard clicks. In today's digital age, where effective user interaction is paramount, cpp-apm provides a simple yet powerful solution for gathering actionable insights.

This tool records and analyzes the frequency of user-initiated actions, allowing you to calculate the Actions Per Minute (APM) over time. By doing so, cpp-apm enables you to:

Monitor Productivity: Keep tabs on user activity to gauge their productivity levels while using software applications or playing games.

Optimize User Experience: Identify areas where users may struggle or experience friction, helping you streamline user interfaces and improve overall user experience.

Enhance Training and Testing: Utilize APM data for training purposes or to evaluate user performance during software testing and quality assurance.

Boost Gaming Performance: Gamers can use cpp-apm to evaluate their performance and pinpoint areas for improvement in fast-paced games.

cpp-apm is an invaluable addition to your toolkit, whether you're a software developer looking to optimize user interfaces, a gamer seeking to refine your skills, or anyone interested in tracking and improving user engagement. With its user-friendly design and real-time APM calculations, cpp-apm empowers you to make data-driven decisions to enhance user interactions and experiences.

## Getting Started

To run this project on a Windows machine, follow these simple steps:

Clone the Repository:

```
git clone https://github.com/your-username/cpp-apm.git
```
Navigate to the Project Directory:

```
cd cpp-apm
```
Generate the Build Files using CMake:
```
cmake .
```
Build the Project:
```
cmake --build .
```
That's it! You now have cpp-apm up and running on your local Windows machine. You can start tracking and analyzing user interactions and actions per minute (APM) to gain valuable insights into user engagement and productivity.

### Prerequisites

Before you begin, ensure you have met the following requirements:

- [CMake](https://cmake.org/) installed on your system.
- A C++ compiler that supports at least C++11.
- [Google Test (GTest)](https://github.com/google/googletest) library for running unit tests.
- [SPDLOG](https://github.com/gabime/spdlog) library for logging.
- Windows operating system (the project is designed to run on Windows).

## Usage

```
./test/bin/test_main.exe
```

## Features

### Main Features
Actions Per Minute (APM) Measurement: The tool tracks and calculates the number of mouse and keyboard clicks to provide APM statistics, giving insights into user activity and engagement.

### Roadmap for Future Features
Enhanced User Interface: Improve the console user interface or develop a graphical user interface (GUI) to enhance user experience and provide a more intuitive way to interact with the tool.

Window Focus: Implement the ability to set rules that allow users to focus the APM tool on specific windows or applications, providing more targeted APM tracking.

## Contributing

Explain how others can contribute to your project. Include guidelines for submitting pull requests or reporting issues.

## License

This project is licensed under the [MIT License](LICENSE.md) - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
