# Tchanz - Ant Colony Simulation

## Project Overview

Tchanz is a sophisticated ant colony simulation system developed as part of the Computer Science curriculum at EPFL (École Polytechnique Fédérale de Lausanne). The project simulates the complex behaviors of ant colonies, including multiple ant types, food gathering, colony defense, and territorial expansion in a discrete 2D world.

The simulation models realistic ant colony dynamics with four distinct ant types (Generator, Collector, Defensor, and Predator), each with specific roles and behaviors. Colonies compete for resources, defend their territory, and grow dynamically based on available food and population constraints.

### Main Objectives
- Simulate realistic ant colony behaviors and interactions
- Model food collection and resource management
- Implement territorial defense and predation mechanics
- Provide visual representation of colony dynamics
- Enable simulation control through an intuitive GUI

## Architecture and Components

The project follows a Model-View-Controller (MVC) architecture pattern, ensuring clean separation of concerns:

```
┌─────────────────────────────────────────────┐
│                   CONTROLLER                │
│                   ┌────────┐                │
│                   │ projet │                │
│                   └────┬───┘                │
│                        │                    │
│                   ┌────▼───┐                │
│                   │  gui   │                │
│                   └────┬───┘                │
└───────────────────────┼─────────────────────┘
                        │
┌───────────────────────┼─────────────────────┐
│         MODEL         │                     │
│                   ┌───▼──────┐              │
│                   │simulation│              │
│                   └────┬─────┘              │
│                        │                    │
│        ┌───────────────┼───────────┐        │
│        │               │           │        │
│   ┌────▼──────┐  ┌─────▼─────┐  ┌──▼───┐    │
│   │fourmiliere│  │nourriture │  │fourmi│    │
│   └───────────┘  └───────────┘  └──────┘    │
│                        │                    │
│                   ┌────▼────┐               │
│                   │ message │               │
│                   └─────────┘               │
└─────────────────────────────────────────────┘
                        │
┌───────────────────────┼─────────────────────┐
│       UTILITIES       │         VIEW        │
│   ┌────────────┐ ┌────▼────┐ ┌─────────┐    │
│   │ squarecell │ │error_sqc│ │ graphic │    │
│   └────────────┘ └─────────┘ └─────────┘    │
└─────────────────────────────────────────────┘
```

### Key Components

- **projet**: Main entry point containing the main() function
- **gui**: GTK+ based graphical user interface management
- **simulation**: Core simulation logic and state management
- **fourmiliere**: Ant colony (anthill) management
- **fourmi**: Ant entity hierarchy and behavior implementation
  - Generator: Colony queen responsible for reproduction
  - Collector: Food gathering ants
  - Defensor: Colony defense units
  - Predator: Attack units for eliminating enemy ants
- **nourriture**: Food resource management
- **squarecell**: Generic 2D grid utilities and geometric calculations
- **graphic**: Low-level drawing operations using Cairo/GTKmm
- **message**: Error message standardization
- **error_squarecell**: Grid validation error handling

## Technologies and Dependencies

### Core Technologies
- **Language**: C++11/14
- **GUI Framework**: GTKmm 3.0
- **Graphics**: Cairo (via GTKmm)
- **Build System**: GNU Make

### System Requirements
- **Compiler**: g++ with C++11 support or higher
- **Operating System**: Linux (tested on EPFL VM)
- **Libraries**:
  - GTKmm 3.0 development libraries
  - Cairo graphics library
  - Standard C++ libraries

### Project Constants
- Grid dimension: 128x128 cells (2^7)
- Maximum anthills: 25
- Ant lifespans: 300 simulation steps
- Food value: 50 units
- Food generation rate: 0.1 probability per step

## Installation and Usage Instructions

### Prerequisites
1. Install required development packages:
```bash
sudo apt-get update
sudo apt-get install g++ make libgtkmm-3.0-dev
```

### Building the Project
1. Extract the project files to a directory
2. Navigate to the project directory:
```bash
cd tchanz-project
```
3. Compile the project:
```bash
make clean
make
```
4. The executable `projet` will be created in the current directory

### Running the Simulation

#### With initial configuration file:
```bash
./projet test_file.txt
```

#### Without configuration (empty simulation):
```bash
./projet
```

### GUI Controls

**Buttons:**
- **Exit**: Close the application
- **Open**: Load a simulation configuration file
- **Save**: Save current simulation state to file
- **Start/Stop**: Toggle continuous simulation
- **Step**: Execute one simulation step
- **Previous/Next**: Navigate between anthills for inspection

**Keyboard Shortcuts:**
- `S`: Start/Stop simulation
- `1`: Step simulation
- `R`: Open file
- `N`: Next anthill
- `P`: Previous anthill

## Directory Structure

```
tchanz-ant-simulation/
│
├── src/                        # Source files
│   ├── core/                   # Core simulation logic
│   │   ├── simulation.cc
│   │   ├── simulation.h
│   │   ├── fourmiliere.cc
│   │   ├── fourmiliere.h
│   │   ├── nourriture.cc
│   │   └── nourriture.h
│   │
│   ├── entities/               # Ant entities
│   │   ├── fourmis.cc
│   │   ├── fourmis.h
│   │   ├── collector.cc
│   │   ├── collector.h
│   │   ├── defensor.cc
│   │   ├── defensor.h
│   │   ├── predator.cc
│   │   ├── predator.h
│   │   ├── generator.cc
│   │   └── generator.h
│   │
│   ├── gui/                    # GUI components
│   │   ├── gui.cc
│   │   ├── gui.h
│   │   ├── graphic.cc
│   │   └── graphic.h
│   │
│   ├── utils/                  # Utility modules
│   │   ├── squarecell.cc
│   │   ├── squarecell.h
│   │   ├── message.cc
│   │   ├── message.h
│   │   ├── error_squarecell.cc
│   │   └── error_squarecell.h
│   │
│   ├── main/                   # Main entry point
│   │   └── projet.cc
│   │
│   └── include/                # Shared headers
│       ├── constantes.h
│       └── constantes.h.gch
│
├── data/                   # Test data files
│   ├── c01.txt
│   ├── c02.txt
│   ├── c03.txt
│   ├── c04.txt
│   ├── f01.txt
│   ├── f02.txt
│   ├── f03.txt
│   ├── f04.txt
│   ├── f05.txt
│   ├── f06.txt
│   ├── f07.txt
│   ├── f08.txt
│   ├── f09.txt
│   ├── f10.txt
│   ├── f11.txt
│   └── f16.txt
│
├── docs/                       # Documentation
│   ├── Project_Data.pdf
│   ├── Rendu1_Data.pdf
│   ├── Rendu2_Data.pdf
│   └── Rendu3_Data.pdf
│
├── scripts/                    # Build and utility scripts
│   ├── build.sh
│   └── test.sh
│
├── README.md                   # Main documentation
├── LICENSE                     # License file
├── Makefile                    # Build configuration
├── .gitignore                  # Git ignore rules
├── .clang-format              # Code formatting rules
└── CHANGELOG.md               # Version history
```

## Configuration File Format

Configuration files define the initial simulation state:

```
# Number of food items
<n_food>
# Food positions (x y for each)
<food_x> <food_y>
...

# Number of anthills
<n_anthills>
# For each anthill:
#   x y size gen_x gen_y total_food n_collectors n_defensors n_predators
<anthill_data>
# Followed by ant positions for each type
```

## API Documentation

### Core Classes

#### Simulation Class
```cpp
class Simulation {
public:
    void lecture_de_fichier(char* nom_fichier);  // Load configuration
    void dessiner();                              // Draw current state
    void execution(vector<Fourmiliere>& F,       // Execute one step
                   vector<Nourriture>& N);
    void reset();                                 // Reset simulation
    void ecriture(string filename, bool b);      // Save state
};
```

#### Fourmiliere (Anthill) Class
```cpp
class Fourmiliere {
public:
    Square get_l();              // Get anthill square
    int get_nbC();               // Get collector count
    int get_nbD();               // Get defensor count
    int get_nbP();               // Get predator count
    void dessiner_f();           // Draw anthill
    bool my_state();             // Check if FREE/CONSTRAINED
};
```

#### Ant Hierarchy
```cpp
class Fourmis {                  // Base ant class
    virtual void move(...);      // Movement logic
    virtual void se_dessiner();  // Drawing logic
};

class Generator : public Fourmis { /* Queen ant */ };
class Collector : public Fourmis { /* Food gatherer */ };
class Defensor : public Fourmis  { /* Defender */ };
class Predator : public Fourmis  { /* Attacker */ };
```

### Utility Functions

#### Grid Operations (squarecell module)
- `Square set_square(int x, int y, int side)` - Create validated square
- `bool superposition_2_carre(Square a, Square b)` - Check overlap
- `void occupation(Square a)` - Mark grid cells as occupied
- `void liberation(Square a)` - Free grid cells
- `double euclide(int x1, int y1, int x2, int y2)` - Calculate distance

## Contributor Guidelines

### Code Style
- Follow EPFL C++ conventions (Conventions_de_Prog_C_2020_10.pdf)
- Use meaningful variable names in lowercase with underscores
- Constants in UPPERCASE
- Types start with capital letter
- Indent with tabs or consistent spaces
- Maximum 87 characters per line
- Maximum 40 lines per function

### Development Process
1. **Testing**: Write unit tests for new features using scaffolding approach
2. **Documentation**: Update headers with contributor percentages
3. **Validation**: Test with provided test files before submission
4. **Compilation**: Ensure clean compilation with no warnings
5. **Memory Management**: Use smart pointers (unique_ptr) for dynamic allocation

### Git Workflow (if using GitHub)
1. Create feature branch from main
2. Implement changes with descriptive commits
3. Test thoroughly
4. Create pull request with description
5. Code review by partner
6. Merge after approval

**Important**: Repository must be private with access limited to team members only.

## Testing

### Unit Testing
Each module should have corresponding unit tests:
```bash
# Example test compilation
g++ -o test_squarecell test_squarecell.cc squarecell.cc error_squarecell.cc
./test_squarecell
```

### Integration Testing
Test files are provided for various scenarios:
- `C01.txt` - Empty simulation
- `f01.txt` - Generator end of life test
- `f02.txt` - Defensor end of life test
- `f03.txt` - Total food test
- `f04.txt` - Birth rate test
- `f05.txt` - Constrained state test
- `f06.txt` - Collector behavior test

### Performance Testing
The simulation should handle:
- 25 simultaneous anthills
- Thousands of ants
- Continuous operation for extended periods

## License Information

This project was developed as part of the Computer Science curriculum at École Polytechnique Fédérale de Lausanne (EPFL).

**Academic License**: This software is provided for educational purposes only. Redistribution and use in source and binary forms, with or without modification, are permitted for academic and educational purposes only, provided that:

1. The source code retains the above copyright notice
2. Redistributions acknowledge EPFL and the original authors
3. The software is not used for commercial purposes
4. Any academic work using this code must cite the original project

**Contributors**: Project developed by students (SCIPER identifiers in mysciper.txt)

**Supervisors**: R. Boulic and collaborators, EPFL

For academic collaboration or questions, contact the Computer Science department at EPFL.

---

© 2021-2022 École Polytechnique Fédérale de Lausanne (EPFL). All rights reserved for educational use.