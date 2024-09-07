# SCSS vs CSS
**SCSS (Sassy CSS)** and **CSS (Cascading Style Sheets)** are both used for styling web pages, but SCSS is a syntax of **Sass (Syntactically Awesome Style Sheets)**, which is a preprocessor that extends CSS with additional features.

Here's a comparison of **SCSS** and **CSS**:

### 1. **Syntax and Features:**

- **CSS**:  
  - The standard style sheet language used for describing the presentation of a web page.
  - Syntax is limited to basic rules, selectors, and properties.
  - Example:
    ```css
    .button {
      color: white;
      background-color: blue;
    }
    ```

- **SCSS**:
  - A superset of CSS, meaning any valid CSS is also valid SCSS.
  - Adds powerful features like variables, nesting, inheritance, and mixins.
  - Example:
    ```scss
    $primary-color: blue;

    .button {
      color: white;
      background-color: $primary-color;

      &:hover {
        background-color: darken($primary-color, 10%);
      }
    }
    ```

### 2. **Variables:**

- **CSS**:  
  CSS has custom properties (variables) but requires repetitive declarations.
  ```css
  :root {
    --primary-color: blue;
  }
  
  .button {
    color: white;
    background-color: var(--primary-color);
  }
  ```

- **SCSS**:  
  SCSS allows the use of variables using the `$` symbol, which can store colors, fonts, or any value you want to reuse throughout the stylesheet.
  ```scss
  $primary-color: blue;

  .button {
    color: white;
    background-color: $primary-color;
  }
  ```

### 3. **Nesting:**

- **CSS**:  
  CSS does not support nesting; you must manually repeat selectors to create specific rules.
  ```css
  .nav {
    background-color: grey;
  }

  .nav ul {
    list-style: none;
  }

  .nav ul li {
    display: inline;
  }
  
  .nav:hover{...}
  .nav.selected{...}
  
  ```

- **SCSS**:  
  SCSS allows for nested rules, which can make code more readable and easier to maintain.
  ```scss
  .nav {
    background-color: grey;

    ul {
      list-style: none;

      li {
        display: inline;
      }
    }
    
    &:hover{..}
    &.selected{..}
  }
  ```

### 4. **Partials and Importing:**

- **CSS**:  
  To import a CSS file, you use the `@import` rule, which causes additional HTTP requests and can slow down page loading.

- **SCSS**:  
  SCSS allows splitting stylesheets into multiple files called "partials," which can be imported into a main stylesheet using `@import`. These imports are combined into a single CSS file, reducing the number of HTTP requests.
  ```scss
  // _buttons.scss
  .button {
    ...
  }

  // main.scss
  @import 'buttons';
  ```

### 5. **Mixins:**

- **CSS**:  
  CSS does not have built-in support for reusable blocks of code.

- **SCSS**:  
  SCSS provides mixins, which are reusable chunks of code that can accept parameters.
  ```scss
  @mixin border-radius($radius) {
    -webkit-border-radius: $radius;
       -moz-border-radius: $radius;
            border-radius: $radius;
  }

  .box {
    @include border-radius(10px);
  }
  ```

### 6. **Functions and Calculations:**

- **CSS**:  
  CSS has limited built-in functions for calculations (like `calc()`) but does not support user-defined functions.

- **SCSS**:  
  SCSS has powerful built-in functions (such as `lighten()`, `darken()`, `percentage()`) and allows you to define your own.
  ```scss
  $base-padding: 10px;
  .box {
    padding: $base-padding * 2;
  }
  ```

### 7. **Inheritance/Extend:**

- **CSS**:  
  CSS does not have a way to extend or inherit styles directly.

- **SCSS**:  
  SCSS allows you to extend a set of properties from one selector to another, making it easier to maintain and write reusable code.
  ```scss
  %button-styles {
    padding: 10px 15px;
    border-radius: 5px;
  }

  .primary-button {
    @extend %button-styles;
    background-color: blue;
  }

  .secondary-button {
    @extend %button-styles;
    background-color: gray;
  }
  ```

### 8. **Output:**

- **CSS**:  
  Written manually, what you see is what you get.

- **SCSS**:  
  Compiled into standard CSS using a preprocessor. The output is a standard CSS file, which browsers can understand.

### 9. **Development Experience:**

- **CSS**:  
  Basic and easy to learn, but can become repetitive and harder to maintain in large projects.

- **SCSS**:  
  Offers a richer development experience with features that make code more organized, modular, and maintainable, especially in large projects.

### When to Use SCSS?

- **Use SCSS** when working on medium to large projects or when you want more flexibility, code reuse, and maintainability.
- **Stick to CSS** if you're working on simple or small-scale projects, or if you don’t need the additional features provided by a preprocessor.

Would you like more specific examples or any other comparison points?

