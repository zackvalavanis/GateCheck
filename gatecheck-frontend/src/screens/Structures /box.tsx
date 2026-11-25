import Box from '@mui/material/Box';
import type { Gate } from '../../types/types';
import { useState, useEffect } from 'react';
import "./box.css"

export default function BoxBasic() {
  const [gates, setGates] = useState<Gate[]>([])
  const [loading, setLoading] = useState(false)


  useEffect(() => {
    const get_gates = async () => {
      setLoading(true);
      try {
        const res = await fetch('/api/state')
        if (!res.ok) {
          console.log("No response");
          return;
        }
        const data = await res.json()
        setGates(data);
      } catch (error) {
        console.log(error);
      } finally {
        setLoading(false)
      }
    }
    get_gates();
  }, [])


  return (
    <>
      {
        loading ? "Loading" : (
          <div className='box-page'>
            {gates.map((gate) => (
              <div key={gate.gate_id}>
                <Box component="section" sx={{ p: 3, border: '1px dashed grey' }}>
                  <p>{gate.gate_id}</p>
                </Box>
              </div>
            ))}
          </div>
        )
      }
    </>
  );
}