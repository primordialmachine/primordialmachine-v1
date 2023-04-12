@{title = "Ring 1 :: Status Library"}
@{tableOfContents = "./api/ring1-library/_toc.ihtml"}
@(>"./_header.html.t")

<h2 id="status-codes">List of status codes</h2>
<p>The following list contains status codes.
A status code is a non-negative implementation specific integer value and a symbolic constant evaluating to this value.
The following table lists all symbolic constant names of status codes and their meanings.</p>

<table>
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_Success</code></td>
  <td>
  Status code indicating success.
  This status code is guaranteed to be the only status code to evaluate to a zero value.
  </td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_ArgumentOutOfRange</code></td>
  <td>Status code indicating a failure because an argument is out of range.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidArgument</code></td>
  <td>Status code indicating a failure because an argument is invalid.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidOperation</code></td>
  <td>Status code indicating a failure because an operation is invalid.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_AllocationFailed</code></td>
  <td>Status code indicating a failure because an allocation failed.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_CollectionFull</code></td>
  <td>Status code indicating a failure because a collection is full.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_CollectionEmpty</code></td>
  <td>Status code indicating a failure because a collection is empty.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_Initialized</code></td>
  <td>Status code indicating a failure because a something is initialized.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_NotInitialized</code></td>
  <td>Status code indicating a failure because something is not initialized.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_DivisionByZero</code></td>
  <td>Status code indicating a failure because a division by zero occurred.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_AlreadyExists</code></td>
  <td>Status code indicating a failure because something exists.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_NotExists</code></td>
  <td>Status code indicating a failure because something does not exists.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidLexics</code></td>
  <td>Status code indicating a failure because of invalid lexics.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidSyntactics</code></td>
  <td>Status code indicating a failure because of invalid syntactics.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidSemantics</code></td>
  <td>Status code indicating a failure because of invalid semantics.</td>
  </tr>
  
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_EnvironmentFailed</code></td>
  <td>Status code indicating a failure because the environment failed.</td>
  </tr>

  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_NumericOverflow</code></td>
  <td>Status code indicating a failure because a numeric overflow occurred.</td>
  </tr>
  
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_ConversionFailed</code></td>
  <td>Status code indicating a failure because a conversion failed.</td>
  </tr>
  
  
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidNumberOfArguments</code></td>
  <td>Status code indicating a failure because a wrong number of arguments was passed.</td>
  </tr>
  
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_InvalidArgumentType</code></td>
  <td>Status code indicating a failure because an argument is of the wrong type.</td>
  </tr>
  
  <tr>
  <td style="width:40%"><code class="inline">Ring1_Status_IndexOutOfBounds</code></td>
  <td>Status code indicating a failure because an index is out of bounds.</td>
  </tr>

</table>

@(>"./_footer.html.t")
