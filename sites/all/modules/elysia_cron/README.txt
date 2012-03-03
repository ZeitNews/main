ELYSIA_CRON
by Eric Berdondini (gotheric)
<eric@void.it>

Features:
- crontab-like scheduling configuration of each job.
- grouping of jobs in channels (parallel lines of execution).
- you can disable all jobs, an entire channel or a single job via configuration.
- force execution of a single cron job on demand
- change the priority/order of job execution
- time statistics of each job and of the whole channel.
- modules can define extra cron tasks, each one with own default cron-rules
  (site administrators can override them by configuration).
- administrators can define custom jobs (call to functions with parameters)
- protection from external cron calling by cron_key or allowed host list.
- ensure all shutdown hook functions launched by cron jobs are launched inside
  cron protection (ex: search_cron() will launch search_update_totals() in a
  shutdown hook).

For installation instructions read INSTALL.TXT

-----------------------------------------------------------------------------
CHANNELS
-----------------------------------------------------------------------------

Channels are groups of tasks. Each channel is a "parallel line" of execution
(= multiple channels can be executed simultaneously).
Tasks inside a channel will be executed sequentially (if they should).

WARNING: It's not recommended to create more than 2 or 3 channels.
Every channel will increase the delay between each cron check (of the same 
channel), because each cron call will cycle between all channels.
So, for example:
If you have 1 channel it will be checked once a minute.
If you have 2 channel each one will be checked every 2 minutes (almost usually, 
when the other one is running it will be checked once a minute).
It you have 10 channels there will be a check every 10 minutes... if you have
a job that should be executed every 5 minutes it won't do so!

-----------------------------------------------------------------------------
RULES AND SCRIPT SYNTAX
-----------------------------------------------------------------------------

1. FIELDS ORDER
---------------------------------

 +---------------- minute (0 - 59)
 |  +------------- hour (0 - 23)
 |  |  +---------- day of month (1 - 31)
 |  |  |  +------- month (1 - 12)
 |  |  |  |  +---- day of week (0 - 7) (Sunday=0)
 |  |  |  |  |
 *  *  *  *  *

Each of the patterns from the first five fields may be either * (an asterisk), 
which matches all legal values, or a list of elements separated by commas 
(see below).

For "day of the week" (field 5), 0 is considered Sunday, 6 is Saturday (7 is 
an illegal value)

A job is executed when the time/date specification fields all match the current 
time and date. There is one exception: if both "day of month" and "day of week" 
are restricted (not "*"), then either the "day of month" field (3) or the "day 
of week" field (5) must match the current day (even though the other of the two 
fields need not match the current day).

2. FIELDS OPERATOR
---------------------------------

There are several ways of specifying multiple date/time values in a field:

* The comma (',') operator specifies a list of values, for example: "1,3,4,7,8"
* The dash ('-') operator specifies a range of values, for example: "1-6", which 
  is equivalent to "1,2,3,4,5,6"
* The asterisk ('*') operator specifies all possible values for a field. For 
  example, an asterisk in the hour time field would be equivalent to 'every hour' 
  (subject to matching other specified fields).
* The slash ('/') operator (called "step") can be used to skip a given number of 
  values. For example, "*/3" in the hour time field is equivalent to 
  "0,3,6,9,12,15,18,21".

3. EXAMPLES
---------------------------------

 */15 * * * : Execute job every 15 minutes
 0 2,14 * * *: Execute job every day at 2:00 and 14:00
 0 2 * * 1-5: Execute job at 2:00 of every working day
 0 12 1 */2 1: Execute job every 2 month, at 12:00 of first day of the month OR at
 every monday.

4. SCRIPTS
---------------------------------

You can use the script section to easily create new jobs (by calling a php function)
or to change the scheduling of an existing job.

Every line of the script can be a comment (if it starts with #) or a job definition.

The syntax of a job definition is:
<-> [rule] <ctx:CONTEXT> [job]

(Tokens betweens [] are mandatory)

* <->: a line starting with "-" means that the job is DISABLED.
* [rule]: a crontab schedule rule. See above.
* <ctx:CONTEXT>: set the context of the job.
* [job]: could be the name of a supported job (for example: 'search_cron') or a
  function call, ending with ; (for example: 'process_queue();').

A comment on the line just preceding a job definition is considered the job 
description.

Remember that script OVERRIDES all settings on single jobs sections or context 
sections of the configuration

5. EXAMPLES OF SCRIPT
---------------------------------

# Search indexing every 2 hours (i'm setting this as the job description)
0 */2 * * * search_cron

# I'll check for module status only on sunday nights 
# (and this is will not be the job description, see the empty line below)

0 2 * * 0 update_status_cron

# Trackback ping process every 15min and on a channel called "net"
*/15 * * * * ctx:net trackback_cron

# Disable node_cron (i must set the cron rule even if disabled)
- */15 * * * * node_cron

# Launch function send_summary_mail('test@test.com', false); every night
# And set its description to "Send daily summary"
# Send daily summary
0 1 * * *  send_summary_mail('test@test.com', false);


-----------------------------------------------------------------------------
MODULE API
-----------------------------------------------------------------------------

You can extend cron functionality in you modules by using elysia_cron api.
With it you can:
- have more than one cron job
- have a different schedule rule for each cron job defined
- set a description for each cron job

To use this functionalities module should implement cronapi hook:

function module_cronapi($op, $job = NULL) {
  ...
}

$op can have 3 values:
- 'list': you should return the list of available jobs, in the form
  array(
    array( 'job' => 'description' ),
    array( 'job' => 'description' ),
    ...
  )
  'job' could be the name of a real function or an identifier used with
  $op = 'execute' (see below).
  Warn: 'job' should be a unique identified, even if it's not a function 
  name.
- 'rule' : when called with this method, $job variable will contain the 
  job name you should return the crun rule of. 
  The rule you return is the default/module preferred schedule rule. 
  An administrator can always override it to fit his needs.
- 'execute' : when the system needs to call the job task, if no function 
  with the same of the job exists, it will call the cronapi with this
  value and with $job filled with the name of the task to execute.
  
Example:
Assume your module needs 2 cron tasks: one executed every hour (process_queue)
and one executed once a day (send_summary_mail).
You can do this with this cronapi:

function module_cronapi($op, $job = NULL) {
  switch ($op) {
    case 'list':
      return array(
        'module_process_queue' => 'Process queue of new data',
        'module_send_summary_mail' => 'Send summary of data processed'
      );
    case 'rule':
      if ($job == 'module_process_queue') return '0 * * * *';
      else return '0 1 * * *';
    case 'execute':
      if ($job == 'module_process_queue') {
        ... do the job ...
      }
      // Just for example, module_send_summary_mail is on a separate
      // function (see below)
  }
}

function module_send_summary_mail() {
  ... do the job ...
}

HANDLING DEFAULT MODULE_CRON FUNCTION
-------------------------------------

To support standard drupal cron all cron hooks (*_cron function) are
automatically added to supported jobs, even if you don't declare them
on cronapi hook (ore you don't implement the hook at all).
However you can define job description and job rule in the same way as
above (considering the job an external function).

Example:
function module_cronapi($op, $job = NULL) {
  switch ($op) {
    case 'list':
      return array(
        'module_cron' => 'Standard cron process',
      );
    case 'rule':
      return '*/15 * * * *';
  }
}

function module_cron() {
  ... 
  // this is the standard cron hook, but with cronapi above
  // it has a default rule (execution every 15 minutes) and
  // a description
  ...
}

-----------------------------------------------------------------------------
THEMING & JOB DESCRIPTION
-----------------------------------------------------------------------------

If you want to have a nicer cron administration page with all modules
description, and assuming only a few modules supports cronapi hooks,
you can add your own description by script (see above) or by 
'elysia_cron_description' theme function.

For example, in your phptemplate theme, you can declare:

function phptemplate_elysia_cron_description($job) {
  switch($job) {
    case 'job 1': return 'First job';
    case 'job 2': return 'Second job';
    default: return theme_elysia_cron_description($job);
  }
}

Note: module default theme_elysia_cron_description($job) already contains
some common tasks descriptions.

-----------------------------------------------------------------------------
CREDITS
-----------------------------------------------------------------------------

Elysia cron is a part of the Elysia project (but could be used stand alone
with no limitation).

Developing is sponsored by :
Void Labs s.n.c
http://www.void.it
