/**
 * Question bonus 1: erreur de conception
 * Lorsque l'on cliquait sur Annuler, on ne pouvait pas choisir à nouveau un
 * fichier. L'implémentation actuelle corrige cela et permet de choisir un
 * nouveau fichier après annulation / complétion.
 */


package compteurjetons;

import java.util.Observable;
import java.util.Observer;

/**
 *
 * @author Samuel Rondeau
 */
public class FenetreCompteur extends javax.swing.JFrame implements Observer {
    
    private Computer cpu = new Computer(this);

    @Override
    public void update(Observable o, Object arg) {
        Integer jetons = ((CompteurJetons) o).getJetons();
        txtJetons.setText(jetons.toString());
        pgrProgres.setValue(((CompteurJetons) o).getProgres());
        // tâche en cours
        if (!cpu.termine()) {
            btnChoisir.setEnabled(false);
            btnCompter.setEnabled(false);
            btnAnnuler.setEnabled(true);
            // aucune tâche en cours
        } else {
            btnChoisir.setEnabled(true);
            btnCompter.setEnabled(true);
            btnAnnuler.setEnabled(false);
        }
        // tâche complétée
        if (((CompteurJetons) o).getProgres() == 100) {
            cpu.msgSucces();
            reinitialiser();
        }
    }

    public FenetreCompteur() {
        initComponents();
        setVisible(true);
        setTitle("Compteur de jetons");
    }

    // Valeurs par défaut
    public void reinitialiser() {
        btnChoisir.setEnabled(true);
        btnCompter.setEnabled(true);
        btnAnnuler.setEnabled(false);
        cpu = new Computer(this);
    }
    
    
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        txtFichier = new javax.swing.JTextField();
        jSeparator1 = new javax.swing.JSeparator();
        btnChoisir = new javax.swing.JButton();
        btnCompter = new javax.swing.JButton();
        btnAnnuler = new javax.swing.JButton();
        pgrProgres = new javax.swing.JProgressBar();
        lblNombre = new javax.swing.JLabel();
        lblProgres = new javax.swing.JLabel();
        txtJetons = new javax.swing.JTextField();
        jMenuBar1 = new javax.swing.JMenuBar();
        mnuFichier = new javax.swing.JMenu();
        mnuOuvrir = new javax.swing.JMenuItem();
        mnuFermer = new javax.swing.JMenuItem();

        jTextArea1.setColumns(20);
        jTextArea1.setRows(5);
        jScrollPane1.setViewportView(jTextArea1);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        btnChoisir.setText("Choisir Fichier");
        btnChoisir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnChoisirActionPerformed(evt);
            }
        });

        btnCompter.setText("Compter");
        btnCompter.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCompterActionPerformed(evt);
            }
        });

        btnAnnuler.setText("Annuler");
        btnAnnuler.setEnabled(false);
        btnAnnuler.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAnnulerActionPerformed(evt);
            }
        });

        lblNombre.setText("Nombre de Jetons:");

        lblProgres.setText("Progres:");

        mnuFichier.setText("Fichier");

        mnuOuvrir.setText("Ouvrir...");
        mnuOuvrir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mnuOuvrirActionPerformed(evt);
            }
        });
        mnuFichier.add(mnuOuvrir);

        mnuFermer.setText("Fermer");
        mnuFermer.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mnuFermerActionPerformed(evt);
            }
        });
        mnuFichier.add(mnuFermer);

        jMenuBar1.add(mnuFichier);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jSeparator1, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(txtFichier, javax.swing.GroupLayout.PREFERRED_SIZE, 283, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(btnChoisir))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(lblNombre)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtJetons, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(58, 58, 58))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(0, 0, Short.MAX_VALUE)
                                .addComponent(lblProgres)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(pgrProgres, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(60, 60, 60)))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(btnCompter, javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(btnAnnuler, javax.swing.GroupLayout.Alignment.TRAILING))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(txtFichier, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnChoisir))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(btnCompter)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(7, 7, 7)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(lblNombre)
                            .addComponent(txtJetons, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(btnAnnuler)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(lblProgres)
                        .addGap(4, 4, 4))
                    .addComponent(pgrProgres, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnChoisirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnChoisirActionPerformed
        cpu = new Computer(this);
        txtFichier.setText(cpu.selectFichier(this));
    }//GEN-LAST:event_btnChoisirActionPerformed

    private void btnAnnulerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnAnnulerActionPerformed
        cpu.arreter();
        txtJetons.setText("annulé");
        reinitialiser();
    }//GEN-LAST:event_btnAnnulerActionPerformed

    private void btnCompterActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCompterActionPerformed
        cpu.executer();
    }//GEN-LAST:event_btnCompterActionPerformed

    private void mnuOuvrirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mnuOuvrirActionPerformed
        txtFichier.setText(cpu.selectFichier(this));
    }//GEN-LAST:event_mnuOuvrirActionPerformed

    private void mnuFermerActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mnuFermerActionPerformed
        // arrêter le swingworker
        cpu.arreter();
        // tout fermer
        setVisible(false);
        dispose();
    }//GEN-LAST:event_mnuFermerActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(FenetreCompteur.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(FenetreCompteur.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(FenetreCompteur.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(FenetreCompteur.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new FenetreCompteur().setVisible(true);
            }
        });
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnAnnuler;
    private javax.swing.JButton btnChoisir;
    private javax.swing.JButton btnCompter;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JTextArea jTextArea1;
    private javax.swing.JLabel lblNombre;
    private javax.swing.JLabel lblProgres;
    private javax.swing.JMenuItem mnuFermer;
    private javax.swing.JMenu mnuFichier;
    private javax.swing.JMenuItem mnuOuvrir;
    private javax.swing.JProgressBar pgrProgres;
    private javax.swing.JTextField txtFichier;
    private javax.swing.JTextField txtJetons;
    // End of variables declaration//GEN-END:variables
}
