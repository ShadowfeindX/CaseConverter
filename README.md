# Evil Case Converter

### Run Commands
___
`./program [stringInCaseType] inputFileName`
`./program [stringInCaseType] inputFileName outputFileName`

### Tests
___
#### Before
```
easy mode
exampleOne
can_be_converted
toAny case
BecauseIt HAS_NO_CONSISTENCY
```
```
medium_mode
WE_ARE_GONNA makeThisALittle
BitHarderNow... punctuationIsA   right_bitch
as is ambiguity amIRight?
bonus_round Ignore 123 the_numbers 456
```
#### After `./program [makeCamel] inFile`
```
easy mode
exampleOne
canBeConverted
toAny case
because
it hasNoConsistency
```
```
mediumMode
weAreGonna makeThisALittle
bitHarderNow... punctuationIsA rightBitch
as is ambiguity amIRight?
bonusRound ignore 123 theNumbers 456
```
#### After `./program [WhoEvenUsesThis] inTEst1`
```
Easy Mode
ExampleOne
CanBeConverted
ToAny Case
BecauseIt HasNoConsistency
```
```
MediumMode
WeAreGonna MakeThisALittle
BitHarderNow... PunctuationIsA RightBitch
As Is Ambiguity AmIRight?
BonusRound Ignore 123 TheNumbers 456
```
#### After `./program [snake_case] 123TestingTesting`
```
easy mode
example_one
can_be_converted
to_any case
because_it has_no_consistency
```
```
medium_mode
we_are_gonna make_this_a_little
bit_harder_now... punctuation_is_a right_bitch
as is ambiguity am_i_right?
bonus_round ignore 123 the_numbers 456
```

#### After `./program [SCREAM_] SEND_HELP_PLEASE`
```
EASY MODE
EXAMPLE_ONE
CAN_BE_CONVERTED
TO_ANY CASE
BECAUSE_IT HAS_NO_CONSISTENCY
```
```
MEDIUM_MODE
WE_ARE_GONNA MAKE_THIS_A_LITTLE
BIT_HARDER_NOW... PUNCTUATION_IS_A RIGHT_BITCH
AS IS AMBIGUITY AM_I_RIGHT?
BONUS_ROUND IGNORE 123 THE_NUMBERS 456
```
