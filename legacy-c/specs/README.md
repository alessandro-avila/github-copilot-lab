# How to write a spec you can test

A spec describes what a module does today in numbered Given/When/Then scenarios: clear enough for anyone to review, and exact enough to become one test per scenario.

## Shape

Every spec in this folder has the same five parts. [checksum.spec.md](checksum.spec.md) is the model.

| Part | What goes in it |
| ---- | --------------- |
| Intro | Two lines: what the spec covers, and its status. A spec stays a draft until a person has reviewed it |
| Scenarios | One `gherkin` block with numbered scenarios. Givens that every scenario shares go in a `Background` |
| Flagged | One row per `@flagged` scenario: the scenario, what the code does today, the question it raises, the decision |
| Not covered | What the spec leaves out, and why |
| Related | Links to the code, the tests and the other specs |

## Rules

### 1. One behaviour per scenario

When a test fails, its scenario tells you what broke.

```gherkin
# Good
Scenario: 3. A code with a letter fails
# Bad: three behaviours in one scenario
Scenario: 3. Codes with a letter, a wrong check digit or one digit fail
```

### 2. Concrete values

Write the real input and the exact result, so anyone can check the scenario by hand.

```gherkin
# Good
Given the parcel code "30123458"
Then you get chute 3
# Bad
Given a valid code
Then you get the right chute
```

### 3. Only observable results

A Then line names something you can see from outside the module: a return value, a hardware call or a printed line. Never internal state, such as a counter.

```gherkin
# Good
Then it diverts the parcel into chute 3
# Bad
Then tries goes up by one
```

The tests in this lab check return values and hardware calls. The harness cannot capture printed lines, so list those under Not covered.

### 4. Plain words, present tense, no implementation details

Use the words operations use, and say what happens, not how the code does it.

```gherkin
# Good
When you look up parcel "30123458"
Then you get chute 3
# Bad: code details, and a wish instead of a fact
When route() loops over table[] with strncmp
Then chute 3 should be returned
```

### 5. Flag odd behaviour, do not fix it

Write what the code does today, even when it looks wrong. Tag the scenario `@flagged` and put the question in the Flagged table, so the team decides.

```gherkin
# Good: what the code does today, flagged
@flagged
Scenario: 6. A two-digit code passes
# Bad: what someone thinks the code should do
Scenario: 6. A two-digit code fails
```

### 6. One test per scenario

Give every scenario one test, with the scenario number in the test's comment, so you can trace each test to its scenario and back.

```c
/* Scenario 3 */
static void code_with_a_letter_fails(void)
{
    CHECK_EQ(0, chk("3012A458"));
}
```

## Related

- [Checksum spec](checksum.spec.md), the model
- [Route spec](route.spec.md), a spec with a `Background`
- [Challenge 1](../../challenges/01-legacy-c-testable/README.md)
