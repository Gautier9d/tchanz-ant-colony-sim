# Changelog

All notable changes to the Tchanz Ant Simulation project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- GitHub repository structure and professional documentation
- CI/CD pipeline with GitHub Actions
- Comprehensive unit and integration tests
- Code formatting with clang-format
- Contributing guidelines and templates

### Changed
- Reorganized source code into logical directories
- Improved build system with better dependency management
- Enhanced error handling and reporting

### Fixed
- Memory leaks in ant destruction
- Grid boundary validation errors
- GUI refresh issues during rapid simulation

## [3.0.0] - 2022-05-22 (Rendu3)

### Added
- Full simulation execution with all ant behaviors
- Predator ant hunting mechanics
- Dynamic anthill growth and constraint states
- Food collection and distribution system
- Ant birth based on food availability
- Complete ant lifecycle management
- Performance optimizations for 25+ anthills

### Changed
- Improved pathfinding algorithms for all ant types
- Enhanced collision detection system
- Optimized rendering for large populations

### Fixed
- Ant overlap detection issues
- Food generation distribution
- Memory management in large simulations

## [2.0.0] - 2022-04-15 (Rendu2)

### Added
- Complete GTKmm GUI implementation
- Interactive simulation controls (Start/Stop/Step)
- Anthill navigation (Previous/Next)
- File save functionality
- Visual representation of all ant types
- Grid rendering with Cairo
- Keyboard shortcuts for controls

### Changed
- Migrated from console to GUI application
- Improved file I/O error handling
- Enhanced visual feedback for simulation states

### Fixed
- Window resizing distortion
- File loading memory leaks
- Drawing performance issues

## [1.0.0] - 2022-04-03 (Rendu1)

### Added
- Initial project structure following MVC architecture
- Basic file reading with error detection
- Squarecell module for grid management
- Ant class hierarchy (Generator, Collector, Defensor, Predator)
- Anthill (Fourmiliere) management
- Food (Nourriture) entities
- Error detection and reporting system
- Makefile build system

### Features
- Configuration file parsing
- Grid boundary validation
- Entity overlap detection
- Memory management for simulation entities
- EPFL coding convention compliance

## [0.1.0] - 2022-03-01

### Added
- Initial project setup
- Basic project documentation
- Development environment configuration

---

## Version History Summary

- **3.x** - Full simulation with complete ant behaviors
- **2.x** - GUI implementation with GTKmm
- **1.x** - Core simulation engine with file I/O
- **0.x** - Initial development and setup

## Upgrade Notes

### From 2.x to 3.x
- No configuration file format changes
- GUI controls remain compatible
- Performance improvements may affect timing

### From 1.x to 2.x
- Requires GTKmm 3.0 installation
- Console mode no longer supported
- Configuration files remain compatible

## License

This project is licensed under the Academic License - see [LICENSE](LICENSE) file for details.