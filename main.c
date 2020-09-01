#include "stdio.h"
#include "nanopb/pb_encode.h"
#include "nanopb/pb_decode.h"
#include "led.pb.h"


uint8_t buffer[128] = {0};
size_t message_length = 0;
bool status = 0;

typedef enum e_led_state
{
    ON  = 1 << 0,
    OFF = 1 << 1,
    TOGGLE = 1 << 2,

}e_led_state;


static void set_led_state(led* self, int l_blue, int l_green, int l_red, int l_yellow)
{
    if (self == NULL)
    {
        return;
    }

    self -> led_blue = l_blue;
    self -> led_green = l_green;
    self -> led_red = l_red;
    self -> led_yellow = l_yellow;

}

int main(int argc, char* argv[])
{
    //Encoding
    {
        
        led led_state = led_init_zero;

        set_led_state(&led_state, ON, OFF, TOGGLE, ON);

        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

        status = pb_encode(&stream, led_fields, &led_state);

        message_length = stream.bytes_written;

        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
    }

    //Decoding
    {

        led led_state = led_init_zero;      
        
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        status = pb_decode(&stream, led_fields, &led_state);

        if (!status)
        {
            printf("\r\n Decoding Failed = %s", PB_GET_ERROR(&stream));
            return 1;
        }

        printf("\r\n State [led_blue] = %i" , led_state.led_blue);
        printf("\r\n State [led_green] = %i" , led_state.led_green);
        printf("\r\n State [led_red] = %i", led_state.led_red);
        printf("\r\n State [led_yellow] = %i \n" , led_state.led_yellow);
        
    }
    
    return 0;
}