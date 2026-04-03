# ESPHome Desk Buddy for ESP32 S3 Box 3

An ESPHome desk buddy for an ESP32 S3 Box 3 with a happiness meter that can be set using HomeAssistant.

## States

### Neutral

When no other state is active, the desk buddy will be in a neutral state. It will show two large eyes that blink and move horizontally.

### Happy

When the happiness meter is above 50, the desk buddy will be happy. It will show two oval half circle eyes that are higher than the neutral state and blink and move horizontally.

### Sad

When the happiness meter is below -50, the desk buddy will be sad. It will show two drooping eyes that are lower than the neutral state and blink and move horizontally.

### Scared

When the desk buddy detects a loud noise, it will be scared. It will show two small round eyes that jitter randomly for a few seconds. This will decrease the happiness meter by 10 points.

### Loved

When the desk buddy's screen is touched, it will feel loved. It will show two red, heart-shaped eyes for a few seconds. This will increase the happiness meter by 10 points.

### Sleepy

When the desk buddy is idle for at least 5 minutes it can become sleepy. It will show two drooping eyes that will slowly close and then quickly open again.

### Sleeping

When the desk buddy is sleepy for 30 seconds it can go to sleep. It will show two closed eyes that slowly move up and down.


## Happiness decay

If the happiness meter hasn't changed, every 15 minutes the happiness meter will decay towards neutral by 5 percent. This means that if the happiness meter is above 0, it will decrease by 5 percent every hour until it reaches 0. If the happiness meter is below 0, it will increase by 5 percent every hour until it reaches 0.
