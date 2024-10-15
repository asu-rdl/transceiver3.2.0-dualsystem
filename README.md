# Dual System MKID Readout IF Up/Down Converter

Purpose built transceiver for ONR/SKIPR telescope readout. Using ASU's board version 3.2.0.

Controller: Arduino Nano Every

# Python API

**Python Class: Transceiver(comport)**
- PARAM: **comport**
    - type: str
    - info: Serial com port used to communicate with the unit

- FUNCTIONS:
    - **set_atten(addr, value) --> (tuple)**
        - *Sets the attenuation of an RF port*
        - addr
            - type: int
            - info: Attenuator address. Exceeding these values will raise an exception
                - addr 1:  System 1 RFOUT
                - addr 2: System 1 RFIN
                - addr 3: System 2 RFOUT
                - addr 4: System 2 RFIN
        - value
            - type: float
            - info: How much attenuation to add from 0 dB to 31.75 dB. 
            Exceeding these values will raise an exception
        - RETURNS
            - (status, message)
                - status: boolean, true when it succeeds, false when it doesn't
                - message: str, "OK" on success or "Some Error Here"
    - **close() --> None**: closes the serial port if open
        - PARAMETERS
            - None
        - RETURNS
            - None
    - **open() --> None**: opens the serial port if closed
        - PARAMETERS
            - None
        - RETURNS
            - None

### Example
```python
import transceiver
slice = transceiver.Transceiver("/dev/ttyACM0")
slice.set_atten(1, 0.0) # set System 1 RFIN to dB of attenuation)
slice.set_atten(2, 15.75) # set System 1 RFOUT to 15.75 dB of attenuation
s, _ = slice.set_atten(3, 0.0)
if s:
    print("IT WORKED!")
slice.close()

```
                



