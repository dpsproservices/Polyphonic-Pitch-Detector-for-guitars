
/* 
 * File:   cJackdDriver.cpp
 * Author: xxac
 * 
 * Created on 17 dicembre 2016, 18.13
 */

#include "cJackdDriver.h"
#include <jack/jack.h>
#include "log_info.h"

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client follows a simple rule: when the JACK transport is
 * running, copy the input port to the output.  When it stops, exit.
 */

static int jack_process(jack_nframes_t nframes, void *arg) 
{
    cJackdDriver* driver = (cJackdDriver*)arg;
    return driver->onJackProcess(nframes);    
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
static void jack_shutdown (void *arg)
{
    cJackdDriver* driver = (cJackdDriver*)arg;
    
    driver->onJackShutdown();
}

cJackdDriver::cJackdDriver():
    m_clientName("pdct"),
    m_client(NULL),
    m_output_port1(NULL),
    m_output_port2(NULL),
    m_input_port1(NULL),
    m_input_port2(NULL),
    m_bufferSize(256),
    m_inputBuffer(NULL),
    m_outputBuffer(NULL),
    m_process(NULL)
{
    
}


cJackdDriver::~cJackdDriver() 
{
    close();
}

int cJackdDriver::open(cString name) 
{
    const char **output_ports;
    const char **input_ports;
    const char *client_name;
    const char *server_name = NULL;
    jack_options_t options = JackNoStartServer;
    jack_status_t status;
    jack_port_t *output_port1, *output_port2;
    jack_port_t *input_port1, *input_port2;
    jack_client_t *client;
    
    m_clientName = name;
    client_name = m_clientName.c_str();

    /* open a client connection to the JACK server */
    client = jack_client_open(client_name, options, &status, server_name);
    if (client == NULL) {
        LOG_ERRO("jack_client_open() failed, status = 0x%2.0x", status);
        if (status & JackServerFailed) {
            LOG_ERRO("Unable to connect to JACK server");
        }
        return -1;
    }
    if (status & JackServerStarted) {
        LOG_INFO("JACK server started");
    }
    if (status & JackNameNotUnique) {
        client_name = jack_get_client_name(client);
        LOG_INFO("unique name `%s' assigned", client_name);
        m_clientName = client_name;
    }
    m_client = client;
    m_bufferSize = jack_get_buffer_size(client);
    if(m_bufferSize<256)m_bufferSize=256;
    m_inputBuffer = new cFloat[2*m_bufferSize];
    m_outputBuffer = new cFloat[2*m_bufferSize];

    /* tell the JACK server to call `process()' whenever
       there is work to be done.
     */
    jack_set_process_callback(client, jack_process, this);

    /* tell the JACK server to call `jack_shutdown()' if
       it ever shuts down, either entirely, or if it
       just decides to stop calling us.
     */
    jack_on_shutdown(client, jack_shutdown, 0);

    /* create two output ports */
    output_port1 = jack_port_register(client, "output1",
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput, 0);

    output_port2 = jack_port_register(client, "output2",
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput, 0);

    if ((output_port1 == NULL) || (output_port2 == NULL)) {
        LOG_ERRO("no more JACK ports available");
        return -1;
    }
    
    m_output_port1 = output_port1;
    m_output_port2 = output_port2;
    
    /* create two input ports */
    input_port1 = jack_port_register(client, "input1",
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsInput, 0);

    input_port2 = jack_port_register(client, "input2",
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsInput, 0);

    if ((input_port1 == NULL) || (input_port2 == NULL)) {
        LOG_ERRO("no more JACK ports available");
        return -1;
    }
    
    m_input_port1 = input_port1;
    m_input_port2 = input_port2;

    /* Tell the JACK server that we are ready to roll.  Our
     * process() callback will start running now. */
    if (jack_activate(client)) {
        LOG_ERRO("cannot activate client");
        return -1;
    }

    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */
    output_ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical | JackPortIsInput);
    if (output_ports == NULL) {
        LOG_ERRO("no physical playback ports");
        return -1;
    }

    if (jack_connect(client, jack_port_name(output_port1), output_ports[0])) {
        LOG_ERRO("cannot connect to system output ports");
    }

    if (jack_connect(client, jack_port_name(output_port2), output_ports[1])) {
        LOG_ERRO("cannot connect to system output ports\n");
    }

    jack_free(output_ports);
    
    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */
    input_ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical | JackPortIsOutput);
    if (input_ports == NULL) {
        LOG_ERRO("no physical capture ports");
        return -1;
    }

    if (jack_connect(client, input_ports[0], jack_port_name(input_port1))) {
        LOG_ERRO("cannot connect to system capture ports");
    }

    if (jack_connect(client, input_ports[1], jack_port_name(input_port2))) {
        LOG_ERRO("cannot connect to system capture ports");
    }

    jack_free(input_ports);

    return 0;
}

int cJackdDriver::close() 
{
    if(m_client!=NULL){
        if(m_inputBuffer!=NULL){
            delete [] m_inputBuffer;
            m_inputBuffer = NULL;
        }
        if(m_outputBuffer!=NULL){
            delete [] m_outputBuffer;
            m_outputBuffer = NULL;
        }
        if (jack_client_close((jack_client_t *)m_client)) {
            LOG_ERRO("cannot close client");
            return -1;
        }
        m_client = NULL;
    }
    
    return 0;
}

int cJackdDriver::onJackProcess(int frames) 
{
    jack_default_audio_sample_t *out1, *out2;
    jack_default_audio_sample_t *inp1, *inp2;
    int i;

    out1 = (jack_default_audio_sample_t*) jack_port_get_buffer((jack_port_t *)m_output_port1, frames);
    out2 = (jack_default_audio_sample_t*) jack_port_get_buffer((jack_port_t *)m_output_port2, frames);
    inp1 = (jack_default_audio_sample_t*) jack_port_get_buffer((jack_port_t *)m_input_port1, frames);
    inp2 = (jack_default_audio_sample_t*) jack_port_get_buffer((jack_port_t *)m_input_port2, frames);
    
    /* inteleave input */
    cFloat* inp = m_inputBuffer;
    for (i = 0; i < frames; i++) {
        (*inp++)=inp1[i];
        (*inp++)=inp2[i];
    }
    
    /* clear output buffer */
    inp = m_outputBuffer;
    for (i = 0; i < frames; i++) {
        (*inp++)=0;
        (*inp++)=0;
    }    
    /* call processor */
    if(m_process!=NULL){
        m_process->process(m_inputBuffer, m_outputBuffer, frames, 2);
    }
    
    /* deinterleve output */
    cFloat* out = m_outputBuffer;
    for (i = 0; i < frames; i++) {
        out1[i] = (*out++);
        out2[i] = (*out++);
    }
    
    return 0; 
}

void cJackdDriver::onJackShutdown()
{
    LOG_ERRO("jackd shutdown");
}

void cJackdDriver::attachProcess(cJackProcess* process) 
{
    m_process = process;
}

