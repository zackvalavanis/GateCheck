import './App.css'
import { BrowserRouter, Routes, Route } from 'react-router'
import { HomePage } from './screens/HomePage/HomePage'


function App() {
  return (
    <BrowserRouter>
      <div className='app-layout'>
        <main className='app-main'>
          <Routes>
            <Route path='/' element={<HomePage />} />
          </Routes>
        </main>
      </div>
    </BrowserRouter>
  )
}

export default App
