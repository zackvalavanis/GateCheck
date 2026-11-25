import Box from '@mui/material/Box';
import { type Gate } from '../../types/types';
import { useState, useEffect } from 'react';
import "./box.css"
import { GateModal } from './gateModal';

export default function BoxBasic() {
  const [gates, setGates] = useState<Gate[]>([])
  const [loading, setLoading] = useState(false)
  const [gateModalShowing, setIsGateModalShowing] = useState<Gate | null>(null)


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


  const handleOpenGateModal = (gate: Gate) => {
    setIsGateModalShowing(gate)
  }


  return (
    <>
      {
        loading ? "Loading" : (
          <div className='box-page'>
            {gates.map((gate) => (
              <div key={gate.gate_id}>
                <Box onClick={() => handleOpenGateModal(gate)} component="section" sx={{ p: 3, border: '1px dashed grey' }}>
                  <p>{gate.gate_id}</p>
                </Box>
              </div>
            ))}
            <GateModal gates={gateModalShowing} show={gateModalShowing != null} onClose={() => setIsGateModalShowing(null)}></GateModal>
          </div >
        )
      }
    </>
  );
}