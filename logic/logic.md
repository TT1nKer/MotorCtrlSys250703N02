# Mermaid Diagram Guide

Mermaid is a JavaScript-based diagramming tool that renders text-based descriptions into diagrams. It's perfect for documenting system architecture, flowcharts, and logic flows.

## Basic Syntax

All Mermaid diagrams start with a code block marked with `mermaid`:

```mermaid
graph TD
    A[Start] --> B[Process]
    B --> C[End]
```

## Common Diagram Types

### 1. Flowcharts (Graphs)

Flowcharts are the most common type, used for process flows and decision trees.

#### Basic Flowchart
```mermaid
graph TD
    A[Start] --> B{Check Condition}
    B -->|Yes| C[Process A]
    B -->|No| D[Process B]
    C --> E[End]
    D --> E
```

#### Motor Control Flowchart Example
```mermaid
graph TD
    A[System Start] --> B[Initialize Motors]
    B --> C[Read Sensor Data]
    C --> D{Error Detected?}
    D -->|Yes| E[Emergency Stop]
    D -->|No| F[Calculate Control Signal]
    F --> G[Apply to Motors]
    G --> H{Target Reached?}
    H -->|No| C
    H -->|Yes| I[System Idle]
    I --> J[Shutdown]
```

### 2. Sequence Diagrams

Show interactions between components over time.

```mermaid
sequenceDiagram
    participant MC as Motor Controller
    participant M1 as Motor 1
    participant M2 as Motor 2
    participant S as Sensor
    
    MC->>S: Request Position
    S-->>MC: Current Position
    MC->>M1: Set Speed 50%
    MC->>M2: Set Speed 30%
    M1-->>MC: Speed Confirmed
    M2-->>MC: Speed Confirmed
```

### 3. Class Diagrams

Show object relationships and structure.

```mermaid
classDiagram
    class MotorController {
        +float currentSpeed
        +float targetSpeed
        +PID pid
        +setSpeed(float speed)
        +getCurrentSpeed()
        +update()
    }
    
    class PID {
        +float kp
        +float ki
        +float kd
        +calculate(float error)
    }
    
    class Motor {
        +int motorId
        +float position
        +float velocity
        +setVelocity(float vel)
        +getPosition()
    }
    
    MotorController --> PID
    MotorController --> Motor
```

### 4. State Diagrams

Show system states and transitions.

```mermaid
stateDiagram-v2
    [*] --> Idle
    Idle --> Running : Start Command
    Running --> Stopping : Stop Command
    Stopping --> Idle : Stop Complete
    Running --> Error : Fault Detected
    Error --> Idle : Reset
    Error --> [*] : Shutdown
```

### 5. Entity Relationship Diagrams

Show data relationships.

```mermaid
erDiagram
    MOTOR ||--o{ SENSOR_DATA : generates
    MOTOR ||--o{ CONTROL_SIGNAL : receives
    MOTOR {
        int motor_id
        string motor_type
        float max_speed
        float current_position
    }
    SENSOR_DATA {
        int sensor_id
        int motor_id
        float position
        float velocity
        timestamp created_at
    }
    CONTROL_SIGNAL {
        int signal_id
        int motor_id
        float target_speed
        float target_position
        timestamp sent_at
    }
```

## Advanced Features

### Styling
```mermaid
graph TD
    A[Start] --> B[Process]
    B --> C[End]
    
    classDef startEnd fill:#e1f5fe
    classDef process fill:#f3e5f5
    
    class A,C startEnd
    class B process
```

### Subgraphs
```mermaid
graph TD
    subgraph Motor_System
        A[Motor 1] --> B[Motor 2]
        B --> C[Motor 3]
    end
    
    subgraph Control_System
        D[PID Controller] --> E[Speed Control]
        E --> F[Position Control]
    end
    
    F --> A
```

### Links and Comments
```mermaid
graph LR
    A[Input] -->|Process Data| B[Output]
    B -.->|Feedback| A
    C[External System] -.->|API Call| B
    
    %% This is a comment
    %% You can add notes like this
```

## Motor Control System Example

Here's a comprehensive example for your motor control system:

```mermaid
graph TD
    subgraph "Input Layer"
        A[User Commands] --> B[Command Parser]
        C[Sensor Inputs] --> D[Data Acquisition]
    end
    
    subgraph "Control Layer"
        B --> E[Command Processor]
        D --> F[Data Processor]
        E --> G[Control Algorithm]
        F --> G
        G --> H[PID Controller]
    end
    
    subgraph "Output Layer"
        H --> I[Motor Driver 1]
        H --> J[Motor Driver 2]
        H --> K[Motor Driver 3]
    end
    
    subgraph "Feedback Loop"
        I --> L[Position Feedback]
        J --> L
        K --> L
        L --> F
    end
    
    subgraph "Safety System"
        M[Emergency Stop] --> N[Safety Monitor]
        N --> O[Fault Handler]
        O --> P[System Shutdown]
    end
    
    G --> N
    L --> N
```

## Tips for Writing Mermaid

1. **Start Simple**: Begin with basic flowcharts before moving to complex diagrams
2. **Use Meaningful Names**: Make node names descriptive
3. **Group Related Elements**: Use subgraphs to organize related components
4. **Add Comments**: Use `%%` for comments to explain complex logic
5. **Test Incrementally**: Build diagrams step by step to catch syntax errors early
6. **Use Consistent Styling**: Apply consistent colors and shapes for similar elements

## Common Syntax Elements

### Node Shapes
- `[]` - Rectangle (default)
- `()` - Rounded rectangle
- `{}` - Diamond (for decisions)
- `(())` - Circle
- `[[]]` - Stadium shape
- `[[]]` - Subroutine shape

### Arrow Types
- `-->` - Solid arrow
- `-.->` - Dotted arrow
- `==>` - Thick arrow
- `--o` - Circle end
- `--x` - Cross end

### Directions
- `TD` - Top to Down
- `BT` - Bottom to Top
- `LR` - Left to Right
- `RL` - Right to Left

This guide should help you create effective diagrams for documenting your motor control system logic and architecture!
