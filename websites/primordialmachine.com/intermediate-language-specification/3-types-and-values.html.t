@{title = "IL Specification: 3. Types and Values"}
@{tableOfContents = "./_toc.ihtml"}
@(>"./_header.html.t")
            <h2>Types and values</h2>

            <p>LLL is a dynamically typed language.
            This means, <em>variables</em> have not type, only <em>stores</em> which are assigned to variables have a type.</p>

            <p>There are 8 types built-in into LLL. Array, Boolean, Function, Integer, Real, String, Structure, and Void.</p>

            <p>The type Void has a single value void representing the absence of any useful value.</p>

            <p>The type Boolean has two values true and false representing logically true and logically false.</p>.

            <p>The type String represents an immutable finite sequences of Bytes.</p>

            <p>The type Integer represents 2-complement 64-bit signed integers, the type Real represents IEEE double precision floating point values.</p>.

            <p>The type Structure represents mappings from names to stores.
            These stores can hold any kind of value, and can be read from and written to.
            Structures can be defined in LLL code or C code.</p>

            <p>The type Array represents a mapping from indices to stores.
            These stores a can hold any kind of value, and can be read from and written to.</p>

            <p>The type Function represents LLL code or C code which can be executed.</p>

            <h2>Programs, Definitions, and Instructions</h2>
            <p>
            An LLL program consists of definitions and instructions.
            Definitions define structure types and function types.
            Instructions inside the body of a function perform computations over values.
            </p>

            <p>
            Instructions perform computations over values.
            There are instructions for creating and manipulating objects of structure types and array types,
            handling errors, invocation and branching and many more.
            Instructions push values on the stack, pop values from the stack, and create and change values.
            </p>
@(>"./_footer.html.t")
