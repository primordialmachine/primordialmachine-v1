  <p><em>Mkx</em> is an interpreter for an intermediate language in the making.
  The purpose of Mkx is intended for science and education.
  </p>
  <h3>Frequently asked questions.</h3>
  <dl>
    <dt>Is it production ready?</dt>
    <dd>Certainly not.</dd>
    <dt>Is it written mkx, Mkx, MKX, or ...?</dt>
    <dd>It is written <em>Mkx</em>.</dd>
    <dt>What does Mkx stand for?</dt>
    <dd>Mkx stands for Mark X.</dd>
    <dt>In what language is Mkx written in?</dt>
    <dd>Mkx is written in C, assembler, and <em>Intermediate Language</em>.</dd>
    <dt>Can I embed Mkx into my C or C++ program?</dt>
    <dd>You can embed Mkx both into C or C++ programs.</dd>
    <dt>What is the <em>Intermediate Language</em>?</dt>
    <dd>It is the language in which programs for the <em>Mkx</em> interpreter.</dd>
    <dt>How often is the website updated?</dt>
    <dd>On a weekly basis.</dd>
    <dt>How often is source code updated?</dt>
    <dd>On a daily or weekly basis.</dd>
    <dt>What is the target audience of <em>Mkx</em>?</dt>
    <dd>The target audience are most likely scholars of practical and theoretical computer science.</dd>
  </dl>
  <p>
  <h3>Getting started</h3>
  <p>Obtain the sources from our <a href="@(repositoryUrl)">Bitbucket repository</a>
  and build it.</p><p>Next, familiarize yourself wit the <em>Intermediate Language</em> (short: <em>IL</em>) which
  is the langugage of the programs <em>Mkx</em> accepts. A specification of the language is provided
  <a href="@(baseurl)intermediate-language-specifiction/">here</a>.
  <h4>Mkx embedding</h4>
  <p>You can embed <em>Mkx</em> into your own program.</p>
  <code class="block">
  #include "Mkx/Interpreter.h"    // For Mkx.<br/>
  #include &lt;stdlib.h&gt; // For EXIT_SUCCESS and EXIT_FAILURE.<br/>
  <br/>
  int<br/>
  main<br/>
  &nbsp;&nbsp;(<br/>
  &nbsp;&nbsp;&nbsp;&nbsp;int argc,<br/>
  &nbsp;&nbsp;&nbsp;&nbsp;char **argv<br/>
  &nbsp;&nbsp;)<br/>
  {<br/>
  &nbsp;&nbsp;// Acquire the interpreter module.<br/>
  &nbsp;&nbsp;Mkx_Interpreter_ModuleHandle handle = Mkx_Interpreter_ModuleHandle_acquire();<br/>
  &nbsp;&nbsp;if (!handle) {<br/>
  &nbsp;&nbsp;&nbsp;&nbsp;return EXIT_FAILURE;<br/>
  &nbsp;&nbsp;}<br/>
  &nbsp;&nbsp;// Create the interpreter context.<br/>
  &nbsp;&nbsp;Mkx_Interpreter_Context* context = Mkx_Interpreter_Context_create();<br/>
  &nbsp;&nbsp;if (!context) {<br/>
  &nbsp;&nbsp;&nbsp;&nbsp;Mkx_Interpreter_ModuleHandle_relinquish(handle);<br/>
  &nbsp;&nbsp;return EXIT_FAILURE;<br/>
  &nbsp;&nbsp;}<br/>
  &nbsp;&nbsp;// Destroy the interpreter context.<br/>
  &nbsp;&nbsp;Mkx_Interpreter_Context_destroy(context);<br/>
  &nbsp;&nbsp;// Relinquish the interpreter module.<br/>
  &nbsp;&nbsp;Mkx_Interpreter_ModuleHandle_relinquish(handle);<br/>
  &nbsp;&nbsp;return EXIT_SUCCESS;<br/>
  }
  </code>
  <h4>Mkx standalone</h4>
  <p>You can use the standalone interpreter.</p>
  <p>Create a file <code class="inline">HelloWorld.lll</code> with the following contents:</p>
  <code class="block">
  # Low Level Language program. Prints "Hello, World!" and exits.<br/>
  push 0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# Print to standard output.<br/>
  push "Hello, World!\n"&nbsp;&nbsp;# The string to print.<br/>
  push 2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# The number of arguments.<br/>
  loadGlobal Core&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# Invoke the function "Core.say".<br/>
  loadField say<br/>
  invoke<br/>
  exit&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;# Exit the program.
  </code>
  <p>Ensure the <code class="inline">Mkx</code> executable and execute the file <code class="inline">HelloWorld.lll</code> file.</p>
  <p><code class="block">
  mkx HelloWorld.lll
  </code></p>
  <p>You should receive as output</p>
  <p><code class="block">
  Hello, World!
  </code></p>
