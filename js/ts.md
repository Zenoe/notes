## js to ts project
To add TypeScript support to a Vite-created JavaScript project, you can follow these steps:

1. Install the required dependencies:

   ```
   npm install --save-dev typescript @types/node @types/react @types/react-dom
   ```

2. Create a `tsconfig.json` file in the root of your project:

   ```
   {
     "compilerOptions": {
       "target": "esnext",
       "module": "esnext",
       "jsx": "preserve",
       "strict": true,
       "esModuleInterop": true,
       "skipLibCheck": true,
       "forceConsistentCasingInFileNames": true
     },
     "include": ["src"]
   }
   ```

3. Rename your `.js` files to `.tsx` (for React components) or `.ts` (for other TypeScript files).

4. Update your `vite.config.js` file to use the `@vitejs/plugin-react-refresh` plugin and configure it to use TypeScript:

   ```
   const reactRefresh = require('@vitejs/plugin-react-refresh');

   module.exports = {
     plugins: [
       reactRefresh()
     ],
     resolve: {
       extensions: ['.ts', '.tsx', '.js', '.json']
     }
   };
   ```

5. Update your `package.json` file to use the TypeScript compiler to build your project:

   ```
   {
     "scripts": {
       "dev": "vite",
       "build": "tsc && vite build"
     }
   }
   ```

6. Restart your development server with `npm run dev`.

That's it! Your Vite-created JavaScript project should now have TypeScript support.

