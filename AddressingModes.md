| **Addressing Mode** | **aaa-field** | **Letters** | **Operand** |
|:--------------------|:--------------|:------------|:------------|
| Immediate           | 000           | i           | OprndSpec   |
| Direct              | 001           | d           | Mem (OprndSpec) |
| Indirect            | 010           | n           | Mem (Mem (OprndSpec)) |
| Stack-relative      | 011           | s           | Mem (SP + OprndSpec) |
| Stack-relative deferred | 100           | sf          | Mem (Mem (SP + OprndSpec)) |
| Indexed             | 101           | x           | Mem (OprndSpec + X ) |
| Stack-indexed       | 110           | sx          | Mem (SP + OprndSpec + X ) |
| Stack-indexed deferred | 111           | sxf         | Mem ( Mem (SP + OprndSpec ) + X ) |

| **Addressing Mode** | **a-field** | **Letters** | **Operand** |
|:--------------------|:------------|:------------|:------------|
| Immediate           | 0           | i           | OprndSpec   |
| Indexed             | 1           | x           | Mem (OprndSpec + X ) |