/*
 * @author Ofir Paz
 * @Version (27/04/2023)
 * This file contains functions to check errors
 * that can occur in the program.
 * */

void system_error(Error)
{

}

void handle_allocation_error(void *ptr)
{
    if (!ptr) /* == NULL, means the space is not allocated */
    {
        SystemError()
    }
}